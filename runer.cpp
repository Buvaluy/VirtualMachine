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

}

void Runer::nextStep()
{
  int indx = mCpu->getPC().toInt();
  qDebug() << "PC: " << indx;
  if(indx > 1000) return;
  QString cmd = mMemory->get(indx);

  QString code = QString(cmd[0]) + QString(cmd[1]);
  int ncode = code.toInt();
  QString typeAdr = QString(cmd[2]);
  QString arg = cmd.remove(0, 3);
  AbstactCommand *cmdImpl = mFactory->createCommand(ncode);
  if(cmdImpl) {
    cmdImpl->execute(arg, typeAdr);
    // Во всех методах я сам увеличиваю PC
    //indx ++;
    //mCpu->setPC(QString::number(indx));
    mDpanel->nextStep();
    mCpu->updateGUI();
  }
}

