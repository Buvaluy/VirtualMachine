#include "compiler.h"

#include <QStringList>
#include <QDebug>

Compiler::Compiler(Memory *mem)
{
    this->mMemory = mem;
    this->mGenCode = new CodeGenerator();
}

Compiler::~Compiler()
{
    delete mGenCode;
}

QString Compiler::parseLabel(QString &strSource)
{
    strSource = strSource.replace("\n", " ");
    QStringList slCommandPair = strSource.split(" ");
    QMap<QString, int> mapLabel;

    for(int i = 0; i < slCommandPair.size(); i ++) {
        QString var = slCommandPair.at(i);
        if(var.indexOf(":") > 0) {
            QString lbl = var;
            int line = i / 2;
            slCommandPair.removeAt(i);
            mapLabel.insert(lbl, line);
        }
    }

    for(auto itr = mapLabel.begin(); itr != mapLabel.end(); itr ++) {
        for(int i = 0; i < slCommandPair.size(); i ++) {
            if(slCommandPair.at(i) == itr.key()) {
                slCommandPair.replace(i, QString::number(itr.value()));
            }
        }
    }

    strSource = slCommandPair.join(" ");

    return strSource;
}

void Compiler::checkCommand(QString &strSource)
{

}

void Compiler::exec(QString &strSource)
{
    strSource = strSource.replace("\n", " ");
    QStringList slCommandPair = strSource.split(" ");
    QString isRegistr, strCode, strCmd, strArg = "000", typeAdrr = "0";
    int indexCmd = 0;
    for(int i = 0; i < slCommandPair.size(); i ++) {
        strCmd = slCommandPair.at(i);
        strCmd = strCmd.toLower();
        if(strCmd == "nop"){
            mMemory->set(indexCmd, "000000");
            indexCmd ++;
            continue;
        }
        isRegistr = slCommandPair.at(i + 1);
        if( isRegistr.contains('r') || isRegistr.contains('R')) //проверка операнда на регистр или число
            strCode = mGenCode->getCode(strCmd + "R");
        else
            strCode = mGenCode->getCode(strCmd);
        if(strCode != "-1") {
            if((i + 1) < slCommandPair.size() ) {
                if(mGenCode->getCode(slCommandPair.at(i + 1)) == "-1") {
                    i ++;
                    strArg = slCommandPair.at(i);

                    typeAdrr = getAddresType((QString)strArg[0] + (QString)strArg[1]);//переделал для Косвенно-регистровой
                    if(typeAdrr == "3"){ //в относительной адресации у нас число стоит между скобками
                        strArg = strArg.remove(0,1); //по этому надо удалить их но оставить число [xxx]
                        for(int n = 0; n < strArg.size(); n++){
                            if(strArg[n] == ']'){
                                strArg.remove(n, 1);
                                break;
                            }
                        }
                    }else if(typeAdrr == "4" && strArg[3] == '+'){ //проверка на алресацию Индексная с постинкрементом
                        typeAdrr = "5";
                        strArg.remove(3, 1);
                        strArg.remove(0, 1);
                    }else if(typeAdrr == "6"){
                        strArg.remove(1, 1);
                        strArg.remove(0, 1);
                    }else if(typeAdrr == "1" || typeAdrr == "2" || typeAdrr == "4"){
                        strArg = strArg.remove(0, 1);
                    }
                }
            }

            if(strArg.size() < 2) { //два if что бы если размер 1 то + 00
                strArg.push_front("0");
            }
            if(strArg.size() < 3) { // если размер 2 то только + 0
                strArg.push_front("0");
            }
            strArg.replace('r', '0');
            QString cmd = strCode + typeAdrr + strArg;
            mMemory->set(indexCmd, cmd);
            indexCmd ++;
        } else {
            // exeption
        }
    }
}

QString Compiler::getAddresType(QString str)
{
    if(str[0] == '#') {
        return "1";
    } else if(str[0] == '@' && !str.contains('r') && !str.contains('R')) {
        return "2";
    } else if(str[0] == '['){
        return "3";
    } else if(str[0] == '@' && ( str.contains('r') || str.contains('R'))){
        return "4";
    } else if(str[0] == '-' && str.contains('@')){
        return "6";
    }
//адресация "5" проверяется после вызова этой функции в exec()
    return "0";
}
