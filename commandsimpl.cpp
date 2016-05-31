#include "commandsimpl.h"


bool CommandImplRead::execute(QString strArg, QString addrType) {
    switch (addrType.toInt()) {
    case 0:
        if(strArg[0].isDigit()){

        }else{

        }
        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    default:
        throw "Bad addressType implRead, type: " + addrType;
        break;
    }
    mCpu->setACC(strArg);
    return true;
}


bool CommandImplWrite::execute(QString strArg, QString addrType) {

    return true;
}


bool CommandImplAdd::execute(QString strArg, QString addrType) {







/*



    bool isDigit;
    int intArg = strArg.toInt(&isDigit);
    int resulAdd;
    QString acc = mCpu->getACC();
    QString operand;
    if(!isDigit){//проверка на то что strArg у нас регистр(R0/R1...) или число.
        if(addrType == ""){//адресация в регистре (взято из методы)
            operand = mCpu->getRegisterValue(strArg.at(1).digitValue());
            resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
        }else if(addrType == "@"){
            QString addressOperand = mCpu->getRegisterValue(strArg.at(1).digitValue());
            operand = mCpu->memory->get(addressOperand.toInt());
            resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
        }else if(addrType == "-@"){
            QString addressOperand = mCpu->getRegisterValue(strArg.at(1).digitValue());
            operand = mCpu->memory->get(addressOperand.toInt() - 1);
            resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
            mCpu->setRegisterValue(strArg.at(1).digitValue(), mCpu->convertIntToReg(addressOperand.toInt() - 1));
        }else if(addrType == "@+"){
            QString addressOperand = mCpu->getRegisterValue(strArg.at(1).digitValue());
            operand = mCpu->memory->get(addressOperand.toInt());
            resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
            mCpu->setRegisterValue(strArg.at(1).digitValue(), mCpu->convertIntToReg(addressOperand.toInt() + 1));
        }else{
            throw "Execute CommandImplAdd bad addrType register";
            return false;
        }
        mCpu->setACC(mCpu->convertIntToReg(resulAdd));
        //Тут искуственно вызывать update для граф части ?
        return true;
    }

    if(addrType == "" || addrType == "["){      //костыль на If else.   '[' адресация, потом поговорим
        operand = mCpu->memory->get(intArg);
        resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
    }else if(addrType == "@"){
        QString addressOperand = mCpu->memory->get(intArg);
        operand = mCpu->memory->get(addressOperand.toInt());
        resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
    }else if(addrType == "#"){
        resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(strArg);
    }else{
        throw "Execute CommandImplAdd bad addrType";
        return false;
    }

    mCpu->setACC(mCpu->convertIntToReg(resulAdd)); */
    return true;
}


bool CommandImplSub::execute(QString strArg, QString addrType) {

    return true;
}


bool CommandImplMul::execute(QString strArg, QString addrType) {

    return true;
}


bool CommandImplDiv::execute(QString strArg, QString addrType) {

    return true;
}
