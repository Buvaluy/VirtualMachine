#include "abstactcommand.h"

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
