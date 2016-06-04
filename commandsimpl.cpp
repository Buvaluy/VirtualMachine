#include "commandsimpl.h"


void CommandImplIn::straight(QString arg)
{
    arg = "0";
    QString ir = mCpu->getIR();
    mCpu->setACC( ir );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    QString mar = mCpu->getPC();
    while(mar.size() < 3){
        mar.push_front('0');
    }
    mCpu->setMAR( mar );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

void CommandImplOut::straight(QString arg)
{
    arg = "0";
    QString acc = mCpu->getACC();
    mCpu->setOR( acc );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setMAR( mCpu->getPC() );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

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

void CommandImplMul::direct(QString arg)
{//#
    while(arg.size() < 6){
        arg.push_front('0');
    }
    QString acc = mCpu->getACC();
    int result = mCpu->convertRegToInt(acc) * mCpu->convertRegToInt(arg);
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

void CommandImplMul::indirect(QString arg)
{//@
    QString mem1 = mMemory->get( arg.toInt() );
    QString adrMem2 = (QString)mem1[3] + (QString)mem1[4] + (QString)mem1[5];
    QString mem2 = mMemory->get( adrMem2.toInt() );
    mCpu->setMAR( adrMem2 );
    mCpu->setMDR( mem2 );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem2[3] + (QString)mem2[4] + (QString)mem2[5];
    int result = mCpu->convertRegToInt( acc ) * mCpu->convertRegToInt( operand );
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setDR( mem2 );
    mCpu->setRA( adrMem2 );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}

void CommandImplMul::straight(QString arg)
{//'0'
    QString mem = mMemory->get( arg.toInt() );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem[3] + (QString)mem[4] + (QString)mem[5];
    int result = mCpu->convertRegToInt( acc ) * mCpu->convertRegToInt( operand );
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setMAR( arg );
    mCpu->setMDR( mem );
    mCpu->setDR( mem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}

void CommandImplDiv::direct(QString arg)
{//#
    while(arg.size() < 6){
        arg.push_front('0');
    }
    QString acc = mCpu->getACC();
    int result = mCpu->convertRegToInt(acc) / mCpu->convertRegToInt(arg);
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

void CommandImplDiv::indirect(QString arg)
{//@
    QString mem1 = mMemory->get( arg.toInt() );
    QString adrMem2 = (QString)mem1[3] + (QString)mem1[4] + (QString)mem1[5];
    QString mem2 = mMemory->get( adrMem2.toInt() );
    mCpu->setMAR( adrMem2 );
    mCpu->setMDR( mem2 );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem2[3] + (QString)mem2[4] + (QString)mem2[5];
    int result = mCpu->convertRegToInt( acc ) / mCpu->convertRegToInt( operand );
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setDR( mem2 );
    mCpu->setRA( adrMem2 );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}

void CommandImplDiv::straight(QString arg)
{//'0'
    QString mem = mMemory->get( arg.toInt() );
    QString acc = mCpu->getACC();
    QString operand = (QString)mem[3] + (QString)mem[4] + (QString)mem[5];
    int result = mCpu->convertRegToInt( acc ) / mCpu->convertRegToInt( operand );
    mCpu->setACC( mCpu->convertIntToReg(result) );
    mCpu->setMAR( arg );
    mCpu->setMDR( mem );
    mCpu->setDR( mem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->incrPC();
}

void CommandImplReadRegister::indirectRegister(QString arg)
{//@
    QString currentComm = mMemory->get(mCpu->getPC().toInt());
    mCpu->setCR(currentComm);
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString operand = (QString)reg.at(3) + (QString)reg.at(4) + (QString)reg.at(5);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    QString op2 = mMemory->get(operand.toInt());
    while(op2.size() < 6){
        op2.push_front('0');
    }
    mCpu->setRAR( arg );
    mCpu->setMDR( op2 );
    mCpu->setACC( op2 );
    mCpu->setRDR( reg );
    mCpu->incrPC();
}

void CommandImplReadRegister::straightRegister(QString arg)
{//'0'
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->setRAR( arg );
    QString operand = mCpu->getRegisterValue( arg.toInt() );//19
    QString mar = mCpu->getPC();
    while(mar.size() < 3){
        mar.push_front('0');
    }
    mCpu->setMAR( mar );
    mCpu->setACC( operand );
    mCpu->setRDR( operand );
    mCpu->incrPC();
}

void CommandImplReadRegister::indexWithPostincrementRegister(QString arg)
{//@R+
    QString currentComm = mMemory->get(mCpu->getPC().toInt());
    mCpu->setCR(currentComm);
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString incrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) + 1 );
    mCpu->setRegisterValue( arg.toInt(), incrReg);
    QString operand = (QString)reg.at(3) + (QString)reg.at(4) + (QString)reg.at(5);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    QString op2 = mMemory->get(operand.toInt());
    while(op2.size() < 6){
        op2.push_front('0');
    }
    mCpu->setRAR( arg );
    mCpu->setMDR( op2 );
    mCpu->setACC( op2 );
    mCpu->setRDR( reg );
    mCpu->incrPC();
}

void CommandImplReadRegister::indexWithPreddekrementomRegister(QString arg)
{//-@R
    QString currentComm = mMemory->get(mCpu->getPC().toInt());
    mCpu->setCR(currentComm);
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString decrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) - 1 );
    mCpu->setRegisterValue( arg.toInt(), decrReg);
    QString operand = (QString)decrReg.at(3) + (QString)decrReg.at(4) + (QString)decrReg.at(5);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    QString op2 = mMemory->get(operand.toInt());
    while(op2.size() < 6){
        op2.push_front('0');
    }
    mCpu->setRAR( arg );
    mCpu->setMDR( op2 );
    mCpu->setACC( op2 );
    mCpu->setRDR( decrReg );
    mCpu->incrPC();
}



void CommandImplWriteRegister::indirectRegister(QString arg)
{//@r
    QString currentComm = mMemory->get(mCpu->getPC().toInt());
    mCpu->setCR(currentComm);
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString operand = (QString)reg.at(3) + (QString)reg.at(4) + (QString)reg.at(5);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    QString acc = mCpu->getACC();
    mMemory->set( operand.toInt(), acc );
    mCpu->setRAR( arg );
    mCpu->setMDR( acc );
    mCpu->setRDR( reg );
    mCpu->incrPC();
}

void CommandImplWriteRegister::straightRegister(QString arg)
{//'0'
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->setRAR( arg );
    QString acc = mCpu->getACC();
    QString mar = mCpu->getPC();
    mCpu->setRegisterValue( arg.toInt(), acc);
    while(mar.size() < 3){
        mar.push_front('0');
    }
    mCpu->setMAR( mar );
    mCpu->setRDR( acc );
    mCpu->incrPC();
}

void CommandImplWriteRegister::indexWithPostincrementRegister(QString arg)
{//@r+
    QString currentComm = mMemory->get(mCpu->getPC().toInt());
    mCpu->setCR(currentComm);
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString incrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) + 1 );
    mCpu->setRegisterValue( arg.toInt(), incrReg);
    QString operand = (QString)reg.at(3) + (QString)reg.at(4) + (QString)reg.at(5);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    QString acc = mCpu->getACC();
    mMemory->set( operand.toInt(), acc );
    mCpu->setRAR( arg );
    mCpu->setMDR( acc );
    mCpu->setRDR( reg );
    mCpu->incrPC();
}

void CommandImplWriteRegister::indexWithPreddekrementomRegister(QString arg)
{//-@r
    QString currentComm = mMemory->get(mCpu->getPC().toInt());
    mCpu->setCR(currentComm);
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString incrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) - 1 );
    mCpu->setRegisterValue( arg.toInt(), incrReg);
    QString operand = (QString)incrReg.at(3) + (QString)incrReg.at(4) + (QString)incrReg.at(5);
    mCpu->setMAR(operand);
    mCpu->setRA(operand);
    QString acc = mCpu->getACC();
    mMemory->set( operand.toInt(), acc );
    mCpu->setRAR( arg );
    mCpu->setMDR( acc );
    mCpu->setRDR( incrReg );
    mCpu->incrPC();
}

void CommandImplAddRegister::indirectRegister(QString arg)
{//@r
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( memory ) + mCpu->convertRegToInt( mCpu->getACC() ) );
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplAddRegister::straightRegister(QString arg)
{//'0'
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) + mCpu->convertRegToInt( mCpu->getACC() ) );
    QString mar = mCpu->getPC();
    while(mar.size() < 3)
        mar.push_front( '0' );

    mCpu->setACC( result );
    mCpu->setDR( reg );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setMAR( mar );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

void CommandImplAddRegister::indexWithPostincrementRegister(QString arg)
{//@r+
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString incrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) + 1 );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( memory ) + mCpu->convertRegToInt( mCpu->getACC() ) );
    mCpu->setRegisterValue( arg.toInt(), incrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplAddRegister::indexWithPreddekrementomRegister(QString arg)
{//-@r
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString decrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) - 1 );
    QString adrMem = (QString)decrReg[3] + (QString)decrReg[4] + (QString)decrReg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( memory ) + mCpu->convertRegToInt( mCpu->getACC() ) );
    mCpu->setRegisterValue( arg.toInt(), decrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplSubRegister::indirectRegister(QString arg)
{//@
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    int regInt = mCpu->convertRegToInt( memory );
    QString result = "0";
    if(regInt < 0)
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) + regInt  );
    else
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) - regInt  );
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplSubRegister::straightRegister(QString arg)
{//'0'
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    int regInt = mCpu->convertRegToInt( reg );
    QString result = "0";
    if(regInt < 0)
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) + regInt  );
    else
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) - regInt  );
    QString mar = mCpu->getPC();
    while(mar.size() < 3)
        mar.push_front( '0' );
    mCpu->setACC( result );
    mCpu->setDR( reg );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setMAR( mar );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

void CommandImplSubRegister::indexWithPostincrementRegister(QString arg)
{//@r+
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString incrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) + 1 );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    int regInt = mCpu->convertRegToInt( memory );
    QString result = "0";
    if(regInt < 0)
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) + regInt  );
    else
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) - regInt  );
    mCpu->setRegisterValue( arg.toInt(), incrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplSubRegister::indexWithPreddekrementomRegister(QString arg)
{//-@r
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString decrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) - 1 );
    QString adrMem = (QString)decrReg[3] + (QString)decrReg[4] + (QString)decrReg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    int regInt = mCpu->convertRegToInt( memory );
    QString result = "0";
    if(regInt < 0)
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) + regInt  );
    else
        result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) - regInt  );
    mCpu->setRegisterValue( arg.toInt(), decrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplMulRegister::indirectRegister(QString arg)
{//@r
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( memory ) * mCpu->convertRegToInt( mCpu->getACC() ) );
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplMulRegister::straightRegister(QString arg)
{//'0'
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) * mCpu->convertRegToInt( mCpu->getACC() ) );
    QString mar = mCpu->getPC();
    while(mar.size() < 3)
        mar.push_front( '0' );

    mCpu->setACC( result );
    mCpu->setDR( reg );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setMAR( mar );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

void CommandImplMulRegister::indexWithPostincrementRegister(QString arg)
{//@r+
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString incrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) + 1 );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( memory ) * mCpu->convertRegToInt( mCpu->getACC() ) );
    mCpu->setRegisterValue( arg.toInt(), incrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplMulRegister::indexWithPreddekrementomRegister(QString arg)
{//-@r
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString decrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) - 1 );
    QString adrMem = (QString)decrReg[3] + (QString)decrReg[4] + (QString)decrReg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( memory ) * mCpu->convertRegToInt( mCpu->getACC() ) );
    mCpu->setRegisterValue( arg.toInt(), decrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}



void CommandImplDivRegister::indirectRegister(QString arg)
{//@r
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) / mCpu->convertRegToInt( memory ) );
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplDivRegister::straightRegister(QString arg)
{//'0'
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) / mCpu->convertRegToInt( reg ) );
    QString mar = mCpu->getPC();
    while(mar.size() < 3)
        mar.push_front( '0' );

    mCpu->setACC( result );
    mCpu->setDR( reg );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setMAR( mar );
    mCpu->setCR( mCpu->getMDR() );
    mCpu->incrPC();
}

void CommandImplDivRegister::indexWithPostincrementRegister(QString arg)
{//@r+
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString incrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) + 1 );
    QString adrMem = (QString)reg[3] + (QString)reg[4] + (QString)reg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) / mCpu->convertRegToInt( memory ) );
    mCpu->setRegisterValue( arg.toInt(), incrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}

void CommandImplDivRegister::indexWithPreddekrementomRegister(QString arg)
{//-@r
    QString reg = mCpu->getRegisterValue( arg.toInt() );
    QString decrReg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) - 1 );
    QString adrMem = (QString)decrReg[3] + (QString)decrReg[4] + (QString)decrReg[5];
    QString memory = mMemory->get( adrMem.toInt() );
    QString result = mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) / mCpu->convertRegToInt( memory ) );
    mCpu->setRegisterValue( arg.toInt(), decrReg);
    mCpu->setACC( result );
    mCpu->setDR( memory );
    mCpu->setRDR( reg );
    mCpu->setRAR( arg );
    mCpu->setMDR( memory );
    mCpu->setMAR( adrMem );
    mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
    mCpu->setRA( adrMem );
    mCpu->incrPC();
}
