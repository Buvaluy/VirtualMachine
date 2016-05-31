#include "compiler.h"

#include <QStringList>

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
  QString strCode, strCmd, strArg = "000", typeAdrr = "0";

  int indexCmd = 0;
  for(int i = 0; i < slCommandPair.size(); i ++) {
    strCmd = slCommandPair.at(i);
    strCmd = strCmd.toLower();
    strCode = mGenCode->getCode(strCmd);

    if(strCode != "-1") {
      if((i + 1) < slCommandPair.size() ) {
        if(mGenCode->getCode(slCommandPair.at(i + 1)) == "-1") {
          i ++;
          strArg = slCommandPair.at(i);

          typeAdrr = getAddresType(strArg.at(0));
          if(typeAdrr != "0")
            strArg = strArg.remove(0, 1);

        }
      }

      if(strArg.size() < 3) {
        strArg.push_front("0");
      }

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
  if(str == "#") {
    return "1";
  } else if(str == "@") {
    return "2";
  }

  return "0";
}
