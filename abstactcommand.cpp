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

void AbstactCommand::push3Times0(QString &str)
{
  while(str.size() < 3)
    str.push_front('0');
}

void AbstactCommand::push6Times0(QString &str)
{
  while(str.size() < 6)
    str.push_front('0');
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

void AbstactCommand::straight(QString strArg){}

void AbstactCommand::straightRegister(QString strArg){}

void AbstactCommand::direct(QString strArg){}

void AbstactCommand::indirect(QString strArg){}

void AbstactCommand::relative(QString strArg){}

void AbstactCommand::indirectRegister(QString strArg){}

void AbstactCommand::indexWithPostincrementRegister(QString strArg){}

void AbstactCommand::indexWithPreddekrementomRegister(QString strArg){}

QStringList AbstactCommand::getMicroCommandList()
{
  QStringList list;
  list << "Micro 1" << "Micro 2" << "Micro 3" << "MIcro 4";
  return list;
}
// return  true if finish
// false if have command for run
bool AbstactCommand::executeMicroCommand(QString arg, QString addr, int currentMicroCommand)
{
  if(currentMicroCommand == 3) {
    this->execute(arg, addr);
    /*int ind = mCpu->getPC().toInt();
    ind ++;
    QString value = QString::number(ind);
    mCpu->setPC(value);*/
    return true;
  }
  return false;
}
