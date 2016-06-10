#ifndef RUNER_H
#define RUNER_H

#include "cpu.h"
#include "memory.h"
#include "commandfactory.h"
#include "commandsimpl.h"

#include "gui/debugpanel.h"

class Runer
{
protected:
  CPU *mCpu;
  Memory *mMemory;
  CommandFactory *mFactory;
  DebugPanel *mDpanel;
public:
  Runer(CPU *cpu, Memory *memory, CommandFactory *factory, DebugPanel* panel);
  ~Runer();

  void run();
  bool nextStep();

};

#endif // RUNER_H
