#ifndef RUNER_H
#define RUNER_H

#include "cpu.h"
#include "memory.h"
#include "commandfactory.h"
#include "commandsimpl.h"

#include "gui/debugpanel.h"
#include "gui/microcommandview.h"

class Runer
{
protected:
  CPU *mCpu;
  Memory *mMemory;
  CommandFactory *mFactory;
  DebugPanel *mDpanel;
  bool isMicroCmd = false;
  int currentMicroCommand;
  MicroCommandView *mView;
public:
  Runer(CPU *cpu, Memory *memory, CommandFactory *factory, DebugPanel* panel, MicroCommandView *view);
  ~Runer();

  void run();
  bool nextStep();
  void clearIndx();

  void setIsMicroCmd(bool value, bool isInitGui);
private: int indx;
};

#endif // RUNER_H
