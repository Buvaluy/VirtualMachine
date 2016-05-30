#ifndef RUNER_H
#define RUNER_H

#include "cpu.h"
#include "memory.h"
#include "commandfactory.h"
#include "commandsimpl.h"

class Runer
{
protected:
  CPU *mCpu;
  Memory *mMemory;
  CommandFactory *mFactory;
public:
  Runer(CPU *cpu, Memory *memory, CommandFactory *factory);
  ~Runer();

  void run();
  void nextStep();

};

#endif // RUNER_H
