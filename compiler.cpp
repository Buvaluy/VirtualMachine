#include "compiler.h"

#include <QStringList>
#include <QDebug>

#include <QTime>
#include <cmath>

Compiler::Compiler(Memory *mem, DebugPanel *panel, QProgressBar *mBar)
{
  this->mMemory = mem;
  this->mGenCode = new CodeGenerator();
  this->out = NULL;
  this->mDpanel = panel;
  this->mBar = mBar;
}

Compiler::~Compiler()
{
  delete mGenCode;
}

void Compiler::setOutPutConsole(QTextEdit *ptr)
{
  this->out = ptr;
}

QString Compiler::parseLabel(QString &strSource)
{
  strSource = strSource.replace("\n", " ");
  QStringList slCommandPair = strSource.split(" ");
  for(int i = 0; i < slCommandPair.size(); i++) {
    if(slCommandPair.at(i) == " " || slCommandPair.at(i).isEmpty())
      slCommandPair.removeAt(i);
  }
  QMap<QString, int> mapLabel;

  for(int i = 0; i < slCommandPair.size(); i ++) {
    QString var = slCommandPair.at(i);
    if(var.indexOf(":") > 0) {
      QString lbl = var.remove(var.length() - 1, 1);
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

void Compiler::exec(QString &strSource)
{
  if(strSource.isEmpty()) return;
  QTime startTime = QTime::currentTime();

  strSource = parseLabel(strSource);
  QStringList slCommandPair = strSource.split(" ");

  mBar->setStyleSheet("QProgressBar {border: 1px solid rgb(83, 83, 83);background-color: rgb(38, 40, 41);border-radius: 5px;} QProgressBar::chunk {background-color: rgb(64, 66, 68);width: 20px; }");
  mBar->setMaximum(slCommandPair.size() - 1);
  mBar->setValue(0);

  QStringList debugList;
  QString isRegistr, strCode, strCmd, strArg = "000", typeAdrr = "0",
          debugArg = " ", debugCmd = " ", resParseCmd = "", error = "";

  int indexCmd = 0;
  for(int i = 0; i < slCommandPair.size(); i ++, mBar->setValue(i)) {
    strCmd = slCommandPair.at(i);
    debugCmd = slCommandPair.at(i);
    strCmd = strCmd.toLower();
    resParseCmd = parseSpecialCommand(strCmd,
                                      i + 1 < slCommandPair.size() ?
                                      slCommandPair.at(i + 1) : " ",
                                      error);

    if(resParseCmd != "-1" && error.isEmpty()) {
      mMemory->set(indexCmd, resParseCmd);
      debugList.append(strCmd);
      indexCmd ++;
    } else if(!error.isEmpty()) {
      fireError(error, indexCmd); return;
    } else {
      if(i < slCommandPair.size()) {
        isRegistr = slCommandPair.at(i + 1);
        strCode = isRegistr.contains('r') || isRegistr.contains('R') ?
                  mGenCode->getCode(strCmd + "R") : mGenCode->getCode(strCmd);
      } else {
        fireError("нет аргумента для команды: " +  strCmd, indexCmd); return;
      }

      if(strCode != "-1") {
        if((i + 1) < slCommandPair.size() ) {
          if(mGenCode->getCode(slCommandPair.at(i + 1)) == "-1") {
            i ++;
            strArg = slCommandPair.at(i); debugArg = strArg;
            parseArguments(strArg, typeAdrr);
          } else {
            fireError("не верный аргумент команды: " +  strCmd, indexCmd); return;
          }
        } else {
          fireError("нет аргумента для команды: " +  strCmd, indexCmd); return;
        }

        while(strArg.size() < 3) strArg.push_front("0");
        strArg = strArg.replace('r', '0');

        debugList.append(debugCmd + " " + debugArg);
        mMemory->set(indexCmd, strCode + typeAdrr + strArg);
        indexCmd ++;
      } else {
        if(out) {
          fireError(" не верная команда", indexCmd);return;
        }
      }
    }
  }
  updateLog(startTime);
  mDpanel->updateCode(debugList);
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
  return "0";
}

void Compiler::fireError(QString str, int line)
{
  out->clear();
  QString outPutMsg = "Ошибка компиляции" + str +
      " в строке: " + QString::number(line);
  mBar->setStyleSheet("QProgressBar {border: 1px solid rgb(83, 83, 83);background-color: rgb(38, 40, 41);border-radius: 5px;} QProgressBar::chunk {background-color: rgb(191, 0, 0);width: 20px; }");
  mBar->setValue(mBar->maximum());
  out->append(outPutMsg);
}

void Compiler::parseArguments(QString &strArg, QString &typeAdrr)
{
  typeAdrr = getAddresType((QString)strArg[0] + (QString)strArg[1]);
  if(typeAdrr == "3"){
    strArg = strArg.remove(0,1);
    for(int n = 0; n < strArg.size(); n++){
      if(strArg[n] == ']'){
        strArg.remove(n, 1);
        break;
      }
    }
  }else if(typeAdrr == "4" && strArg[3] == '+'){
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

QString Compiler::parseSpecialCommand(const QString &strCmd, QString args, QString &error)
{
  if(strCmd == "nop"){
    return "000000";
  }else if(strCmd == "in"){
    return "010000";
  }else if(strCmd == "out"){
    return "020000";
  }else if(strCmd == "htl"){
    return "090000";
  }
  else if(strCmd == "jrnz"){
    QStringList argsJRNZ = args.split(",");
    if(argsJRNZ.size() < 2)
      error = "Error неверный агрумент для клманды jrnz (формат R,MMM)";
    else
      return  "17" + argsJRNZ.at(0) + argsJRNZ.at(1);
  }
  return "-1";
}

void Compiler::updateLog(QTime &startTime)
{
  QTime endTime = QTime::currentTime();
  if(out) {
    out->clear();
    QString secnd = QString::number(abs(endTime.second() - startTime.second()));
    QString min   = QString::number(abs(endTime.minute() - startTime.minute()));
    QString msecnd = QString::number(abs(endTime.msec() - startTime.msec()));
    QString outPutMsg = "Компиляция прошла успешно время: " +
        formatTime(min, 2) + ":" +
        formatTime(secnd, 2) + ':' +
        formatTime(msecnd, 3) ;
    mBar->setValue(mBar->maximum());
    out->append(outPutMsg);
  }
}


QString Compiler::formatTime(QString str, int cnt)
{
  while(str.size() < cnt) {
    str.push_front("0");
  }
  return str;
}
