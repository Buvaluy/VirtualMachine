#include "runer.h"

#include <QDebug>

void Runer::setIsMicroCmd(bool value, bool isInitGui)
{
  isMicroCmd = value;

  if(isMicroCmd && isInitGui) {
    int indx = mCpu->getPC().toInt();
    if(indx > 1000) return;
    QString cmd = mMemory->get(indx);
    if(cmd == "090000") return;

    QString code = QString(cmd[0]) + QString(cmd[1]);
    int ncode = code.toInt();
    QString typeAdr = QString(cmd[2]);
    QString arg = cmd.remove(0, 3);
    AbstactCommand *cmdImpl = mFactory->createCommand(ncode);
    mView->updateGui(cmdImpl->getListMicroCommand(), 0);
    delete cmdImpl;
  }

}

Runer::Runer(CPU *cpu, Memory *memory, CommandFactory *factory, DebugPanel* panel, MicroCommandView *view)
{
  mCpu = cpu;
  mMemory = memory;
  mFactory = factory;
  mDpanel = panel;
  mDpanel->resetCurrentCommand();
  mView = view;
  currentMicroCommand = 0;
  indx = 0;
}

Runer::~Runer()
{

}

void Runer::run()
{
  while(nextStep()) {}
}
//Выполнение одной команды из памяти ОЗУ по адресу текущей команды
// (PC) при нажатии кнопки в GUI 'Шаг'
bool Runer::nextStep()
{
  if(indx > 1000) return false;
  QString cmd = mMemory->get(indx);
  if(cmd == "090000") return false;

  QString code = QString(cmd[0]) + QString(cmd[1]);
  int ncode = code.toInt();
  QString typeAdr = QString(cmd[2]);
  QString arg = cmd.remove(0, 3);
  AbstactCommand *cmdImpl = mFactory->createCommand(ncode);
  if(cmdImpl) {
    if(isMicroCmd) {
      if(cmdImpl->executeMicroCommand(arg, typeAdr, currentMicroCommand)) {
        currentMicroCommand = 0;
        mDpanel->nextStep();
        indx = mCpu->getPC().toInt();
        //mCpu->updateGUI();
      } else {
        currentMicroCommand ++;
      }
      //qDebug() << "PC " << mCpu->getPC() << "    MC " << currentMicroCommand << cmdImpl->getListMicroCommand();
      mView->updateGui(cmdImpl->getListMicroCommand(), currentMicroCommand);
      mCpu->updateGUI();
    } else {
      cmdImpl->execute(arg, typeAdr);
      mDpanel->nextStep();
      mCpu->updateGUI();
      indx = mCpu->getPC().toInt();
    }
  }
  delete cmdImpl;

  return true;
}

void Runer::clearIndx()
{
    indx = 0;
}

