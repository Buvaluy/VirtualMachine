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

void CommandImplWrite::indirect(QString arg)
{//@
    QString acc = mCpu->getACC();
    QString operand = mMemory->get(arg.toInt());
    operand = (QString)operand[3] + (QString)operand[4] + (QString)operand[5];
    mMemory->set(operand.toInt(), acc);
    mCpu->setMDR(acc);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    mCpu->setCR(mMemory->get(mCpu->getPC().toInt()));
    mCpu->incrPC();
}

void CommandImplWrite::straight(QString arg)
{//'0'
    QString acc = mCpu->getACC();
    mMemory->set(arg.toInt(), acc);
    mCpu->setMDR(acc);
    mCpu->setMAR(arg);
    mCpu->setCR(mMemory->get(mCpu->getPC().toInt()));
    mCpu->incrPC();
}

void CommandImplAdd::direct(QString arg)
{//#
    while(arg.size() < 6){
        arg.push_front('0');
    }
    QString acc = mCpu->getACC();
    int result = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(arg);
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setDR( arg );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    QString mar = mCpu->getPC();
    while(mar.size() < 3){
        mar.push_front('0');
    }
    mCpu->setMAR( mar );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

void CommandImplAdd::indirect(QString arg)
{//@
    QString mem1 = mMemory->get( arg.toInt() );
    QString adrMem2 = (QString)mem1[3] + (QString)mem1[4] + (QString)mem1[5];
    QString mem2 = mMemory->get( adrMem2.toInt() );
    mCpu->setMAR( adrMem2 );
    mCpu->setMDR( mem2 );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem2[3] + (QString)mem2[4] + (QString)mem2[5];
    int result = mCpu->convertRegToInt( acc ) + mCpu->convertRegToInt( operand );
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setDR( mem2 );
    mCpu->setRA( adrMem2 );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}

void CommandImplAdd::straight(QString arg)
{//'0'
    QString mem = mMemory->get( arg.toInt() );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem[3] + (QString)mem[4] + (QString)mem[5];
    int result = mCpu->convertRegToInt( acc ) + mCpu->convertRegToInt( operand );
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setMAR( arg );
    mCpu->setMDR( mem );
    mCpu->setDR( mem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}

void CommandImplSub::direct(QString arg)
{//#
    while(arg.size() < 6){
        arg.push_front('0');
    }
    QString acc = mCpu->getACC();
    int result = 0;
    if( mCpu->convertRegToInt( arg ) < 0 ){
        result = mCpu->convertRegToInt( acc ) + mCpu->convertRegToInt( arg );
    }else{
        result = mCpu->convertRegToInt( acc ) - mCpu->convertRegToInt( arg );
    }
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setDR( arg );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    QString mar = mCpu->getPC();
    while(mar.size() < 3){
        mar.push_front('0');
    }
    mCpu->setMAR( mar );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

void CommandImplSub::indirect(QString arg)
{//@
    QString mem1 = mMemory->get( arg.toInt() );
    QString adrMem2 = (QString)mem1[3] + (QString)mem1[4] + (QString)mem1[5];
    QString mem2 = mMemory->get( adrMem2.toInt() );
    mCpu->setMAR( adrMem2 );
    mCpu->setMDR( mem2 );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem2[3] + (QString)mem2[4] + (QString)mem2[5];
    int result = 0;
    if( mCpu->convertRegToInt( operand ) < 0 ){
        result = mCpu->convertRegToInt( acc ) + mCpu->convertRegToInt( operand );
    }else{
        result = mCpu->convertRegToInt( acc ) - mCpu->convertRegToInt( operand );
    }
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setDR( mem2 );
    mCpu->setRA( adrMem2 );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}

void CommandImplSub::straight(QString arg)
{//'0'
    QString mem = mMemory->get( arg.toInt() );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem[3] + (QString)mem[4] + (QString)mem[5];
    int result = 0;
    if( mCpu->convertRegToInt( operand ) < 0 ){
        result = mCpu->convertRegToInt( acc ) + mCpu->convertRegToInt( operand );
    }else{
        result = mCpu->convertRegToInt( acc ) - mCpu->convertRegToInt( operand );
    }
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setMAR( arg );
    mCpu->setMDR( mem );
    mCpu->setDR( mem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}
