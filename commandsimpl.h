#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H

#include "cpu.h"
#include "abstactcommand.h"

class CommandImplAdd : public AbstactCommand
{
public:

  bool execute(QString strArg) override {
    CPU* impl = CPU.getCpuImpl();

    return true;
  }

};




#endif // COMMANDSIMPL_H
