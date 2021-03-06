#include "commandsimpl.h"

/*В данном файле commandImpl.cpp реализованны функции
 * для разных комманд, при чем если у команды есть
 * несколько видов адресации, то у неё несколько
 * реализаций (по методу на адресацию одной команды)
 * - входные данные во всех функция QString arg,
 * где arg - операнд с которым будет работать
 * команды при той или инной адресации.
 * Так же входными данными является QString
 * полученный с ОЗУ и CPU через атрибут этого класса
 * mMemory, mCpu
 * - выходным данными является изменение данных регистров
 * CPU через атрибут этого класса mCPU.
 *
 * straight - прямая
 * direct - непосредственая
 * inderect - косвеная
 * straightRegistr - прямая регистровая
 * inderectRegistr - косвено-регистровая
 * indexWithPostincrementRegister - индексная с постинкрементом
 * indexWithPreddekrementomRegister - индексная с предекрментом
 *
 */
void CommandImplIn::straight(QString arg)
{
  arg = "0";
  QString ir = mCpu->getIR();
  mCpu->setACC( ir );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  mCpu->incrPC();
}

void CommandImplIn::setMicroCommandList()
{
  QStringList list;
  list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
       << "Acc := IR" << "EMD_COMMAND";
  listMicroCommand = list;
}

void CommandImplIn::straightMC(QString arg, int currentMicroCommand)
{
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  mCpu->setACC( mCpu->getIR() );
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

void CommandImplOut::setMicroCommandList()
{
  QStringList list;
  list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
       << "OR := Acc" << "EMD_COMMAND";
  listMicroCommand = list;
}

void CommandImplOut::straightMC(QString arg, int currentMicroCommand)
{
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  mCpu->setOR( mCpu->getACC() );
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
  push6Times0( op2 );
  mCpu->setMDR(op2);
  mCpu->setACC(op2);
  mCpu->incrPC();
}

void CommandImplRead::straight(QString arg)
{
  // если обыная '0'
  mCpu->setCR(mMemory->get(mCpu->getPC().toInt()));
  QString operand = mMemory->get(arg.toInt());//19
  push3Times0( arg );
  push6Times0( operand );
  mCpu->setMAR(arg);
  mCpu->setMDR(operand);
  mCpu->setACC(operand);
  mCpu->incrPC();
}

void CommandImplRead::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "Acc := MDR" << "EMD_COMMAND";
  else if(getTypeAddr() == "1")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "Acc := ADR" << "EMD_COMMAND";
  else if(getTypeAddr() == "2")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "RA := MDR" << "MAR := RA"
         << "MRd" << "Acc := MDR" << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplRead::directMC(QString arg, int currentMicroCommand)
{//#
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  mCpu->setACC( mCpu->getADR() );
}

void CommandImplRead::indirectMC(QString arg, int currentMicroCommand)
{//@
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setMAR( mCpu->getADR() );
    break;
  case 5:
    mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
    break;
  case 6:{
    QString mdr = mCpu->getMDR();
    QString ra = (QString)mdr[3] + (QString)mdr[4] + (QString)mdr[5];
    mCpu->setRA( ra );
    break;}
  case 7:
    mCpu->setMAR( mCpu->getRA() );
    break;
  case 8:
    mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
    break;
  case 9:
    mCpu->setACC( mCpu->getMDR() );
    break;
  default:
    break;
  }
}

void CommandImplRead::straightMC(QString arg, int currentMicroCommand)
{// 0
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setMAR( mCpu->getADR() );
    break;
  case 5:
    mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
    break;
  case 6:
    mCpu->setACC( mCpu->getMDR() );
    break;
  default:
    break;
  }
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

void CommandImplWrite::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MDR := Acc" << "MWr" << "EMD_COMMAND";
  else if(getTypeAddr() == "2")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "RA := MDR" << "MAR := RA"
         << "MDR := Acc" << "MWr" << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplWrite::indirectMC(QString arg, int currentMicroCommand)
{
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setMAR( mCpu->getADR() );
    break;
  case 5:
    mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
    break;
  case 6:{
    QString mdr = mCpu->getMDR();
    QString ra = (QString)mdr[3] + (QString)mdr[4] + (QString)mdr[5];
    mCpu->setRA( ra );
    break;}
  case 7:
    mCpu->setMAR( mCpu->getRA() );
    break;
  case 8:
    mCpu->setMDR( mCpu->getACC() );
    break;
  case 9:
    mMemory->set( mCpu->getMAR().toInt(), mCpu->getMDR());
    break;
  default:
    break;
  }
}

void CommandImplWrite::straightMC(QString arg, int currentMicroCommand)
{
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setMAR( mCpu->getADR() );
    break;
  case 5:
    mCpu->setMDR( mCpu->getACC() );
    break;
  case 6:
    mMemory->set( mCpu->getMAR().toInt(), mCpu->getMDR() );
    break;
  default:
    break;
  }
}

void CommandImplAdd::direct(QString arg)
{//#
  push6Times0( arg );
  QString acc = mCpu->getACC();
  int result = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(arg);
  mCpu->setACC( mCpu->convertIntToReg(result) );
  mCpu->setDR( arg );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  QString mar = mCpu->getPC();
  push3Times0( mar );
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

void CommandImplAdd::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "DR := MDR" << "ALU <- COP"
         << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "1")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "DR := ADR" << "ALU <- COP" << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "2")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "RA := MDR" << "MAR := RA"
         << "MRd" << "DR := MDR" << "ALU <- COP" << "Start ALU"
         << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplAdd::directMC(QString arg, int currentMicroCommand)
{//#
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setDR( mCpu->getADR() );
    break;
  case 5:
    break;
  case 6:
    mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) +
                                         mCpu->convertRegToInt( mCpu->getDR() ) ) );
    break;
  default:
    break;
  }
}

void CommandImplAdd::indirectMC(QString arg, int currentMicroCommand)
{//@
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setMAR( mCpu->getADR() );
    break;
  case 5:
    mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
    break;
  case 6:{
    QString mdr = mCpu->getMDR();
    QString ra = (QString)mdr[3] + (QString)mdr[4] + (QString)mdr[5];
    mCpu->setRA( ra );
    break;}
  case 7:
    mCpu->setMAR( mCpu->getRA() );
    break;
  case 8:
    mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
    break;
  case 9:
    mCpu->setDR( mCpu->getMDR() );
    break;
  case 10:

    break;
  case 11:
    mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) +
                                         mCpu->convertRegToInt( mCpu->getDR() ) ) );
    break;
  default:
    break;
  }
}

void CommandImplAdd::straightMC(QString arg, int currentMicroCommand)
{//0
  arg = arg;
  setMicroCommandList();
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setMAR( mCpu->getADR() );
    break;
  case 5:
    mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
    break;
  case 6:
    mCpu->setDR( mCpu->getMDR() );
    break;
  case 7:
    break;
  case 8:
    mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) +
                                         mCpu->convertRegToInt( mCpu->getDR() ) ) );
    break;
  default:
    break;
  }
}

void CommandImplSub::direct(QString arg)
{//#
  push6Times0( arg );
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
  push3Times0( mar );
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

void CommandImplSub::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "DR := MDR" << "ALU <- COP"
         << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "1")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "DR := ADR" << "ALU <- COP" << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "2")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "RA := MDR" << "MAR := RA"
         << "MRd" << "DR := MDR" << "ALU <- COP" << "Start ALU"
         << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplSub::directMC(QString arg, int currentMicroCommand)
{
  arg = arg;
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setDR( mCpu->getADR() );
    break;
  case 5:
    break;
  case 6:{
    if(mCpu->convertRegToInt( mCpu->getDR() ) >= 0 )
      mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) -
                                         mCpu->convertRegToInt( mCpu->getDR() ) ) );
    else
      mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) +
                                         mCpu->convertRegToInt( mCpu->getDR() ) ) );
    break;}
  default:
    break;
  }
}

void CommandImplSub::indirectMC(QString arg, int currentMicroCommand)
{
  //@
    arg = arg;
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setMAR( mCpu->getADR() );
      break;
    case 5:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 6:{
      QString mdr = mCpu->getMDR();
      QString ra = (QString)mdr[3] + (QString)mdr[4] + (QString)mdr[5];
      mCpu->setRA( ra );
      break;}
    case 7:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 8:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 9:
      mCpu->setDR( mCpu->getMDR() );
      break;
    case 10:

      break;
    case 11:{
      if(mCpu->convertRegToInt( mCpu->getDR() ) >= 0 )
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) -
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      else
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) +
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      break;}
    default:
      break;
    }
}

void CommandImplSub::straightMC(QString arg, int currentMicroCommand)
{
  //0
    arg = arg;
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setMAR( mCpu->getADR() );
      break;
    case 5:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 6:
      mCpu->setDR( mCpu->getMDR() );
      break;
    case 7:
      break;
    case 8:{
      if(mCpu->convertRegToInt( mCpu->getDR() ) >= 0 )
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) -
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      else
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) +
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      break;}
    default:
      break;
    }
}

void CommandImplMul::direct(QString arg)
{//#
  push6Times0( arg );
  QString acc = mCpu->getACC();
  int result = mCpu->convertRegToInt(acc) * mCpu->convertRegToInt(arg);
  mCpu->setACC( mCpu->convertIntToReg(result) );
  mCpu->setDR( arg );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  QString mar = mCpu->getPC();
  push3Times0( mar );
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

void CommandImplMul::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "DR := MDR" << "ALU <- COP"
         << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "1")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "DR := ADR" << "ALU <- COP" << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "2")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "RA := MDR" << "MAR := RA"
         << "MRd" << "DR := MDR" << "ALU <- COP" << "Start ALU"
         << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplMul::directMC(QString arg, int currentMicroCommand)
{
  arg = arg;
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setDR( mCpu->getADR() );
    break;
  case 5:
    break;
  case 6:
      mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) *
                                         mCpu->convertRegToInt( mCpu->getDR() ) ) );
    break;
  default:
    break;
  }
}

void CommandImplMul::indirectMC(QString arg, int currentMicroCommand)
{
  //@
    arg = arg;
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setMAR( mCpu->getADR() );
      break;
    case 5:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 6:{
      QString mdr = mCpu->getMDR();
      QString ra = (QString)mdr[3] + (QString)mdr[4] + (QString)mdr[5];
      mCpu->setRA( ra );
      break;}
    case 7:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 8:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 9:
      mCpu->setDR( mCpu->getMDR() );
      break;
    case 10:

      break;
    case 11:
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) *
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      break;
    default:
      break;
    }
}

void CommandImplMul::straightMC(QString arg, int currentMicroCommand)
{
  //0
    arg = arg;
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setMAR( mCpu->getADR() );
      break;
    case 5:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 6:
      mCpu->setDR( mCpu->getMDR() );
      break;
    case 7:
      break;
    case 8:
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) *
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      break;
    default:
      break;
    }
}

void CommandImplDiv::direct(QString arg)
{//#
  push6Times0( arg );
  QString acc = mCpu->getACC();
  int result = mCpu->convertRegToInt(acc) / mCpu->convertRegToInt(arg);
  mCpu->setACC( mCpu->convertIntToReg(result) );
  mCpu->setDR( arg );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  QString mar = mCpu->getPC();
  push3Times0( mar );
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

void CommandImplDiv::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "DR := MDR" << "ALU <- COP"
         << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "1")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "DR := ADR" << "ALU <- COP" << "Start ALU" << "EMD_COMMAND";
  else if(getTypeAddr() == "2")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "MAR := ADR" << "MRd" << "RA := MDR" << "MAR := RA"
         << "MRd" << "DR := MDR" << "ALU <- COP" << "Start ALU"
         << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplDiv::directMC(QString arg, int currentMicroCommand)
{
  arg = arg;
  if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
    duplicateMicroCommand(currentMicroCommand);
    return;
  }
  switch (currentMicroCommand) {
  case 4:
    mCpu->setDR( mCpu->getADR() );
    break;
  case 5:
    break;
  case 6:
      mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) /
                                         mCpu->convertRegToInt( mCpu->getDR() ) ) );
    break;
  default:
    break;
  }
}

void CommandImplDiv::indirectMC(QString arg, int currentMicroCommand)
{
  //@
    arg = arg;
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setMAR( mCpu->getADR() );
      break;
    case 5:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 6:{
      QString mdr = mCpu->getMDR();
      QString ra = (QString)mdr[3] + (QString)mdr[4] + (QString)mdr[5];
      mCpu->setRA( ra );
      break;}
    case 7:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 8:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 9:
      mCpu->setDR( mCpu->getMDR() );
      break;
    case 10:

      break;
    case 11:
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) /
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      break;
    default:
      break;
    }
}

void CommandImplDiv::straightMC(QString arg, int currentMicroCommand)
{
  //0
    arg = arg;
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setMAR( mCpu->getADR() );
      break;
    case 5:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 6:
      mCpu->setDR( mCpu->getMDR() );
      break;
    case 7:
      break;
    case 8:
        mCpu->setACC( mCpu->convertIntToReg( mCpu->convertRegToInt( mCpu->getACC() ) /
                                           mCpu->convertRegToInt( mCpu->getDR() ) ) );
      break;
    default:
      break;
    }
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
  push6Times0( op2 );
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
  push3Times0( mar );
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
  push6Times0( op2 );
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
  push6Times0( op2 );
  mCpu->setRAR( arg );
  mCpu->setMDR( op2 );
  mCpu->setACC( op2 );
  mCpu->setRDR( decrReg );
  mCpu->incrPC();
}

void CommandImplReadRegister::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "RRd" << "Acc := RDR" << "EMD_COMMAND";
  else if(getTypeAddr() == "4")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "RRd" << "RA := RDR" << "MAR := RA"
         << "MRd" << "Acc := MDR" << "EMD_COMMAND";
  else if(getTypeAddr() == "5")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "RRd" << "RA := RDR" << "MAR := RA"
         << "MRd" << "Acc := MDR" << "INC_GR" << "EMD_COMMAND";
  else if(getTypeAddr() == "6")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "DEC_GR" << "RRd" << "RA := RDR"
         << "MAR := RA" << "MRd" << "Acc := MDR" << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplReadRegister::indirectRegisterMC(QString arg, int currentMicroCommand)
{
  //@
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRDR( mCpu->getRegisterValue( mCpu->getRAR().toInt() ) );
      break;
    case 6:{
      QString rdr = mCpu->getRDR();
      QString ra = (QString)rdr[3] + (QString)rdr[4] + (QString)rdr[5];
      mCpu->setRA( ra );
      break;}
    case 7:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 8:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 9:
      mCpu->setACC( mCpu->getMDR() );
      break;
    default:
      break;
    }
}

void CommandImplReadRegister::straightRegisterMC(QString arg, int currentMicroCommand)
{
  // 0
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRDR( mCpu->getRegisterValue( mCpu->getRAR().toInt() ) );
      break;
    case 6:
      mCpu->setACC( mCpu->getRDR() );
      break;
    default:
      break;
    }
}

void CommandImplReadRegister::indexWithPostincrementRegisterMC(QString arg, int currentMicroCommand)
{
  //@+
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRDR( mCpu->getRegisterValue( mCpu->getRAR().toInt() ) );
      break;
    case 6:{
      QString rdr = mCpu->getRDR();
      QString ra = (QString)rdr[3] + (QString)rdr[4] + (QString)rdr[5];
      mCpu->setRA( ra );
      break;}
    case 7:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 8:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 9:
      mCpu->setACC( mCpu->getMDR() );
      break;
    case 10:
      mCpu->setRegisterValue( mCpu->getRAR().toInt(),
            mCpu->convertIntToReg( mCpu->convertRegToInt(
                                     mCpu->getRegisterValue( mCpu->getRAR().toInt() ) ) +1 ) );
      break;
    default:
      break;
    }
}

void CommandImplReadRegister::indexWithPreddekrementomRegisterMC(QString arg, int currentMicroCommand)
{
  //-@
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRegisterValue( mCpu->getRAR().toInt(),
            mCpu->convertIntToReg( mCpu->convertRegToInt(
                                     mCpu->getRegisterValue( mCpu->getRAR().toInt() ) ) - 1 ) );
      break;
    case 6:
      mCpu->setRDR( mCpu->getRegisterValue( mCpu->getRAR().toInt() ) );
      break;
    case 7:{
      QString rdr = mCpu->getRDR();
      QString ra = (QString)rdr[3] + (QString)rdr[4] + (QString)rdr[5];
      mCpu->setRA( ra );
      break;}
    case 8:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 9:
      mCpu->setMDR( mMemory->get( mCpu->getMAR().toInt() ) );
      break;
    case 10:
      mCpu->setACC( mCpu->getMDR() );
      break;
    default:
      break;
    }
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
  push3Times0( mar );
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

void CommandImplWriteRegister::setMicroCommandList()
{
  QStringList list;
  if(getTypeAddr() == "0")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "RDR := Acc" << "RWr" << "EMD_COMMAND";
  else if(getTypeAddr() == "4")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "RRd" << "RA := RDR" << "MAR := RA"
         << "MDR := Acc" << "MWr" << "EMD_COMMAND";
  else if(getTypeAddr() == "5")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "RRd" << "RA := RDR" << "MAR := RA"
         << "MDR := Acc" << "MWr" << "INC_GR" << "EMD_COMMAND";
  else if(getTypeAddr() == "6")
    list << "MAR := PC" << "MRd" << "CR := MDR" << "PC := PC + 1"
         << "RAR := CR5" << "DEC_GR" << "RRd" << "RA := RDR"
         << "MAR := RA" << "MDR := Acc" << "MWr" << "EMD_COMMAND";

  listMicroCommand = list;
}

void CommandImplWriteRegister::indirectRegisterMC(QString arg, int currentMicroCommand)
{
  //@
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRDR( mCpu->getRegisterValue( mCpu->getRAR().toInt() ) );
      break;
    case 6:{
      QString rdr = mCpu->getRDR();
      QString ra = (QString)rdr[3] + (QString)rdr[4] + (QString)rdr[5];
      mCpu->setRA( ra );
      break;}
    case 7:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 8:
      mCpu->setMDR( mCpu->getACC() );
      break;
    case 9:
      mCpu->setRegisterValue( mCpu->getRAR().toInt(),
                              mCpu->getRDR() );
      break;
    default:
      break;
    }
}

void CommandImplWriteRegister::straightRegisterMC(QString arg, int currentMicroCommand)
{
  // 0
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRDR( mCpu->getACC() );
      break;
    case 6:
      mCpu->setRegisterValue( mCpu->getRAR().toInt(),
                              mCpu->getRDR() );
      break;
    default:
      break;
    }
}

void CommandImplWriteRegister::indexWithPostincrementRegisterMC(QString arg, int currentMicroCommand)
{
  //@+
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRDR( mCpu->getRegisterValue( mCpu->getRAR().toInt() ) );
      break;
    case 6:{
      QString rdr = mCpu->getRDR();
      QString ra = (QString)rdr[3] + (QString)rdr[4] + (QString)rdr[5];
      mCpu->setRA( ra );
      break;}
    case 7:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 8:
      mCpu->setMDR( mCpu->getACC() );
      break;
    case 9:
      mCpu->setRegisterValue( mCpu->getRAR().toInt(),
                              mCpu->getMDR());
      break;
    case 10:
      mMemory->set( mCpu->getRAR().toInt(),
            mCpu->convertIntToReg( mCpu->convertRegToInt(
                                     mCpu->getRegisterValue( mCpu->getRAR().toInt() ) ) +1 ) );
      break;
    default:
      break;
    }
}

void CommandImplWriteRegister::indexWithPreddekrementomRegisterMC(QString arg, int currentMicroCommand)
{
  //-@
    arg = arg;
    setMicroCommandList();
    if(currentMicroCommand >= 0 && currentMicroCommand <= 3){
      duplicateMicroCommand(currentMicroCommand);
      return;
    }
    switch (currentMicroCommand) {
    case 4:
      mCpu->setRAR( (QString)mCpu->getADR()[2] );
      break;
    case 5:
      mCpu->setRegisterValue( mCpu->getRAR().toInt(),
            mCpu->convertIntToReg( mCpu->convertRegToInt(
                                     mCpu->getRegisterValue( mCpu->getRAR().toInt() ) ) - 1 ) );
      break;
    case 6:
      mCpu->setRDR( mCpu->getRegisterValue( mCpu->getRAR().toInt() ) );
      break;
    case 7:{
      QString rdr = mCpu->getRDR();
      QString ra = (QString)rdr[3] + (QString)rdr[4] + (QString)rdr[5];
      mCpu->setRA( ra );
      break;}
    case 8:
      mCpu->setMAR( mCpu->getRA() );
      break;
    case 9:
      mCpu->setMDR( mCpu->getACC() );
      break;
    case 10: mMemory->set( mCpu->getRAR().toInt(),
                           mCpu->convertIntToReg( mCpu->convertRegToInt(
                                                    mCpu->getRegisterValue( mCpu->getRAR().toInt() ) ) +1 ) );
                     break;
    default:
      break;
    }
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
  push3Times0( mar );
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
  push3Times0( mar );
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
  push3Times0( mar );
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
  push3Times0( mar );
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

void CommandImplJmp::straight(QString arg)
{
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  mCpu->setPC( arg );
}

void CommandImplJz::straight(QString arg)
{
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  if( mCpu->convertRegToInt( mCpu->getACC() ) == 0 )
    mCpu->setPC( arg );
  else
    mCpu->incrPC();
}

void CommandImplJnz::straight(QString arg)
{
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  if( mCpu->convertRegToInt( mCpu->getACC() ) != 0 )
    mCpu->setPC( arg );
  else
    mCpu->incrPC();
}

void CommandImplJs::straight(QString arg)
{
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  if( mCpu->convertRegToInt( mCpu->getACC() ) < 0 )
    mCpu->setPC( arg );
  else
    mCpu->incrPC();
}

void CommandImplJns::straight(QString arg)
{
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  qDebug() << "JNS: " << mCpu->convertRegToInt( mCpu->getACC() ) << "arg: " << arg;
  if( mCpu->convertRegToInt( mCpu->getACC() ) > 0 )
    mCpu->setPC( arg );
  else
    mCpu->incrPC();
}

void CommandImplJo::straight(QString arg)
{
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  if( mCpu->getOV().toInt() == 1 )
    mCpu->setPC( arg );
  else
    mCpu->incrPC();
}

void CommandImplJno::straight(QString arg)
{
  QString mar = mCpu->getPC();
  push3Times0( mar );
  mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  if( mCpu->getOV().toInt() == 0 )
    mCpu->setPC( arg );
  else
    mCpu->incrPC();
}

void CommandImplJrnz::straight(QString arg)
{
  arg = arg;
  QString mar = mCpu->getPC();
  QString memory = mMemory->get( mCpu->getPC().toInt() );
  QString numberRegistr = (QString)memory[2];
  QString goToPC = (QString)memory[3] + (QString)memory[4] + (QString)memory[5];
  QString reg = mCpu->getRegisterValue( numberRegistr.toInt() );
  push3Times0( mar );
  mCpu->setMDR( memory );
  mCpu->setMAR( mar );
  mCpu->setCR( mCpu->getMDR() );
  mCpu->setRA( numberRegistr );
  reg = mCpu->convertIntToReg( mCpu->convertRegToInt( reg ) - 1 );
  mCpu->setRegisterValue( numberRegistr.toInt(), reg );
  if( reg.toInt() > 0 )
    mCpu->setPC( goToPC );
  else
    mCpu->incrPC();
}


void CommandImplPush::straight(QString arg)
{
  QString sp = mCpu->getSP();
  QString reg = mCpu->getRegisterValue( arg.toInt() );
  if(sp.toInt() == 0)
    sp = "999";
  else
    sp = QString::number( sp.toInt() - 1 );
  mCpu->setRDR( reg );
  mCpu->setRAR( arg );
  mCpu->setMDR( reg );
  mCpu->setMAR( sp );
  mCpu->setSP( sp );
  mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
  mMemory->set( sp.toInt(), reg );
  mCpu->incrPC();
}

void CommandImplPop::straight(QString arg)
{
  QString sp = mCpu->getSP();
  if( sp.toInt() == 0 ){
    mCpu->incrPC();
    return;
  }
  QString mem = mMemory->get( sp.toInt() );
  mCpu->setRDR( mem );
  mCpu->setRAR( arg );
  mCpu->setMDR( mem );
  mCpu->setMAR( sp );
  mCpu->setCR( mMemory->get( mCpu->getPC().toInt() ) );
  mCpu->setRegisterValue( arg.toInt(), mem);
  sp = QString::number( sp.toInt() + 1 );
  if(sp.toInt() == 1000)
    sp = "000";
  mCpu->setSP( sp );
  mCpu->incrPC();
}

void CommandImplCall::straight(QString arg)
{
  QString mdr = mMemory->get( mCpu->getPC().toInt() );
  QString sp = mCpu->getSP();
  QString pc = mCpu->getPC();
  if( sp.toInt() == 0)
    sp = "999";
  else
    sp = QString::number( sp.toInt() - 1 );
  push6Times0( arg );
  push6Times0( pc );
  mCpu->setMDR( arg );
  mCpu->setMAR( sp );
  mCpu->setCR( mdr );
  mMemory->set( sp.toInt(), pc);
  mCpu->setSP( sp );
  mCpu->setPC( arg );
}

void CommandImplRet::straight(QString arg)
{
  QString mdr = mMemory->get( mCpu->getPC().toInt() );
  QString sp = mCpu->getSP();
  if( sp.toInt() == 0 ){
    mCpu->incrPC();
    return;
  }
  QString pc = mMemory->get( sp.toInt() );
  push6Times0( arg );
  mCpu->setMDR( arg );
  mCpu->setMAR( sp );
  mCpu->setCR( mdr );
  //mMemory->set( sp.toInt(), mCpu->getPC() );
  sp = QString::number( sp.toInt() + 1 );
  if(sp.toInt() == 1000)
    sp = "000";
  mCpu->setSP( sp );
  mCpu->setPC( QString::number( pc.toInt() + 1 ) );
}
