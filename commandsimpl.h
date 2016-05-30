#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H

#include "cpu.h"
#include "abstactcommand.h"

class CommandImplAdd : public AbstactCommand
{

public:

  CommandImplAdd(CPU *cpu) {
    setCpu(cpu);
  }

  bool execute(QString strArg, QString addrType) override {

    return true;
  }

};




#endif // COMMANDSIMPL_H
