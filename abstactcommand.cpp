#include "abstactcommand.h"

#include <QDebug>

QString AbstactCommand::getName() const
{
  return name;
}

void AbstactCommand::setName(const QString &value)
{
  name = value;
}

QString AbstactCommand::getCode() const
{
  return code;
}

void AbstactCommand::setCode(const QString &value)
{
  code = value;
}

QString AbstactCommand::getArg() const
{
  return arg;
}

void AbstactCommand::setArg(const QString &value)
{
  arg = value;
}

QString AbstactCommand::getTypeAddr() const
{
  return typeAddr;
}

void AbstactCommand::setTypeAddr(const QString &value)
{
  typeAddr = value;
}

CPU *AbstactCommand::getCpu() const
{
    return mCpu;
}

void AbstactCommand::setCpu(CPU *cpu)
{
  mCpu = cpu;
}

void AbstactCommand::setMemory(Memory *memory)
{
  this->mMemory = memory;
}

AbstactCommand::AbstactCommand()
{

}

bool AbstactCommand::execute(QString strArg, QString typeAddr)
{
  if(typeAddr == "6") {// -@R
    indexWithPreddekrementomRegister(strArg);
  } else if(typeAddr == "1") { //#
    direct(strArg);
  } else if(typeAddr == "2") { //@
    indirect(strArg);
  } else if(typeAddr == "3") { // []
    relative(strArg);
  } else if(typeAddr == "5") {// @R+
    indexWithPostincrementRegister(strArg);
  } else if(typeAddr == "4"){ // @R
    indirectRegister(strArg);
  } else {
    straightRegister(strArg);
    straight(strArg);
  }

  return true;
}

void AbstactCommand::straight(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}

void AbstactCommand::straightRegister(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}

void AbstactCommand::direct(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}

void AbstactCommand::indirect(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}

void AbstactCommand::relative(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}

void AbstactCommand::indirectRegister(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}

void AbstactCommand::indexWithPostincrementRegister(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}

void AbstactCommand::indexWithPreddekrementomRegister(QString strArg)
{
  qDebug() << "Не использованная адресация" << strArg;
}
