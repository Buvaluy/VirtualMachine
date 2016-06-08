#include "runer.h"

#include <QDebug>

Runer::Runer(CPU *cpu, Memory *memory, CommandFactory *factory, DebugPanel *panel)
{
  mCpu = cpu;
  mMemory = memory;
  mFactory = factory;
  mDpanel = panel;
  mDpanel->resetCurrentCommand();
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
    cmdImpl->execute(arg, typeAdr);
    mDpanel->nextStep();
    mCpu->updateGUI();
  }
  delete cmdImpl;
  return true;
}

