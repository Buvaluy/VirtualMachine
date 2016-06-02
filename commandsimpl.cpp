#include "commandsimpl.h"


void CommandImplRead::direct(QString arg)
{
  while(arg.count() < 6){
      arg.push_front('0');
  }
  mCpu->setACC(arg);
}

void CommandImplRead::indirect(QString arg)
{
  // Действие если коственная
    QString mem = mMemory->get(arg.toInt());
    QString operand = mMemory->get(mem.toInt());
    while(arg.operand() < 6){
        arg.push_front('0');
    }
    mCpu->setACC(operand);
}

void CommandImplRead::straight(QString arg)
{
  // если обыная
    QString operand = mMemory->get(arg.toInt());
    while(arg.operand() < 6){
        arg.push_front('0');
    }
    mCpu->setACC(operand);
}

void CommandImplReadRegister::indirectRegister(QString arg)
{

}

void CommandImplReadRegister::straightRegister(QString arg)
{

}

void CommandImplReadRegister::indexWithPostincrementRegister(QString arg)
{

}

void CommandImplReadRegister::indexWithPreddekrementomRegister(QString arg)
{

}
