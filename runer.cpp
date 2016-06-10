#include "runer.h"

#include <QDebug>

void Runer::setIsMicroCmd(bool value)
{
  isMicroCmd = value;

  if(isMicroCmd) {
    int indx = mCpu->getPC().toInt();
    if(indx > 1000) return;
    QString cmd = mMemory->get(indx);
    if(cmd == "090000") return;

    QString code = QString(cmd[0]) + QString(cmd[1]);
    int ncode = code.toInt();
    QString typeAdr = QString(cmd[2]);
    QString arg = cmd.remove(0, 3);
    AbstactCommand *cmdImpl = mFactory->createCommand(ncode);
    mView->updateGui(cmdImpl->getMicroCommandList(), 0);
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
}

Runer::~Runer()
{

}

void Runer::run()
{
  while(nextStep()) {}
}

bool Runer::nextStep()
{
  int indx = mCpu->getPC().toInt();
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
        mCpu->updateGUI();
      } else {
        currentMicroCommand ++;
      }
      mView->updateGui(cmdImpl->getMicroCommandList(), currentMicroCommand);
    } else {
      cmdImpl->execute(arg, typeAdr);
      mDpanel->nextStep();
      mCpu->updateGUI();
    }
  }
  delete cmdImpl;
  return true;
}

