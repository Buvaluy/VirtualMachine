#include "commandfactory.h"

CommandFactory::CommandFactory(CPU *cpu)
{
  this->impl = cpu;
}

AbstactCommand *CommandFactory::createCommand(int code)
{
  return mCommands.value(code, NULL);
}
