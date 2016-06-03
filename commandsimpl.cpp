#include "commandsimpl.h"


void CommandImplRead::direct(QString arg)
{//#
  while(arg.count() < 6){
      arg.push_front('0');
  }
  mCpu->setACC(arg);
  QString cellComand = mMemory->get(mCpu->getPC().toInt());
  mCpu->setMDR(cellComand);
  mCpu->setMAR(mCpu->getPC());
  mCpu->setCR(cellComand);
  mCpu->incrPC();
}

void CommandImplRead::indirect(QString arg)
{
  // Действие если коственная @

    QString currentComm = mMemory->get(mCpu->getPC().toInt());
    mCpu->setCR(currentComm);
    QString mem = mMemory->get(arg.toInt());
    QString operand = (QString)mem.at(3) + (QString)mem.at(4) + (QString)mem.at(5);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    QString op2 = mMemory->get(operand.toInt());
    while(op2.size() < 6){
        op2.push_front('0');
    }
    mCpu->setMDR(op2);
    mCpu->setACC(op2);
    mCpu->incrPC();
}

void CommandImplRead::straight(QString arg)
{
  // если обыная '0'
    mCpu->setCR(mMemory->get(mCpu->getPC().toInt()));
    QString operand = mMemory->get(arg.toInt());//19
    while(arg.size() < 3){
        arg.push_front('0');
    }
    while(operand.size() < 6){
        arg.push_front('0');
    }
    mCpu->setMAR(arg);
    mCpu->setMDR(operand);
    mCpu->setACC(operand);
    mCpu->incrPC();
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
