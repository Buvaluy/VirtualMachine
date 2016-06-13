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

/*
 * Следующие два метода нобходмы для вставки '0' в начало
 * QString. Это связанно с тем, что регистры в CPU
 * имею разные рязрядности , 3 или 6.
 * - Входнные данные: данные регистра, которые нужно дополнить '0'
 * переданны как аргумент функции по ссылке
 * - Выходные данные: теже данные которые были поданны на вход
 * но с изменением (передача по ссылке)
 */
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

QStringList AbstactCommand::getListMicroCommand() const
{
  return listMicroCommand;
}

void AbstactCommand::duplicateMicroCommand(int currentMicroCommand)
{
  switch (currentMicroCommand) {
  case 0:{
    QString mar = mCpu->getPC();
    push3Times0( mar );
    mCpu->setMAR( mar );
    break;
  }
  case 1:
    mCpu->setMDR( mMemory->get( mCpu->getPC().toInt() ) );
    break;
  case 2:
    mCpu->setCR( mCpu->getMDR() );
    break;
  case 3:
    mCpu->incrPC();
    break;
  }
}

AbstactCommand::AbstactCommand()
{

}
/*
 * Вызов нужной функции по типу адресации для
 * конкретной команды. Команда определяется с
 * помощью фабричного патерна.
 * - Входные данные: операнд и типАдресации
 * - Выходные данные: отсутсвуют. Типо bool
 * в качестве возращаемого параментра функции
 * не используется
 */
bool AbstactCommand::execute(QString strArg, QString typeAddr)
{
  setTypeAddr( typeAddr );
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

/*
 * Методы перегружаеммые в классах своих команд
 */
void AbstactCommand::straight(QString strArg){strArg = strArg;}

void AbstactCommand::straightRegister(QString strArg){strArg = strArg;}

void AbstactCommand::direct(QString strArg){strArg = strArg;}

void AbstactCommand::indirect(QString strArg){strArg = strArg;}

void AbstactCommand::relative(QString strArg){strArg = strArg;}

void AbstactCommand::indirectRegister(QString strArg){strArg = strArg;}

void AbstactCommand::indexWithPostincrementRegister(QString strArg){strArg = strArg;}

void AbstactCommand::indexWithPreddekrementomRegister(QString strArg){strArg = strArg;}

void AbstactCommand::straightMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

void AbstactCommand::straightRegisterMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

void AbstactCommand::directMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

void AbstactCommand::indirectMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

void AbstactCommand::relativeMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

void AbstactCommand::indirectRegisterMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

void AbstactCommand::indexWithPostincrementRegisterMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

void AbstactCommand::indexWithPreddekrementomRegisterMC(QString strArg, int currentMicroCommand)
{strArg = strArg; currentMicroCommand = currentMicroCommand;}

/*
 * После реализации будет описание
 *
 */
//QStringList AbstactCommand::getMicroCommandList()
//{
//  QStringList list;
//  list << "Micro 1" << "Micro 2" << "Micro 3" << "Micro 4";
//  return list;
//}
// return  true if finish
// false if have command for run
bool AbstactCommand::executeMicroCommand(QString arg, QString addr, int currentMicroCommand)
{
  setTypeAddr( addr );//возможно потом удалить
  if(addr == "6") {// -@R
    indexWithPreddekrementomRegisterMC(arg, currentMicroCommand);
  } else if(addr == "1") { //#
    directMC(arg, currentMicroCommand);
  } else if(addr == "2") { //@
    indirectMC(arg, currentMicroCommand);
  } else if(addr == "3") { // []
    relativeMC(arg, currentMicroCommand);
  } else if(addr == "5") {// @R+
    indexWithPostincrementRegisterMC(arg, currentMicroCommand);
  } else if(addr == "4"){ // @R
    indirectRegisterMC(arg, currentMicroCommand);
  } else {
    straightRegisterMC(arg, currentMicroCommand);
    straightMC(arg, currentMicroCommand);
  }
  if(listMicroCommand.size() == currentMicroCommand && listMicroCommand.size() != 0)
    return true;
  return false;
}
