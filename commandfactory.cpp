#include "commandfactory.h"
#include "commandsimpl.h"
#include <QDebug>

CommandFactory::CommandFactory(CPU *cpu, Memory *memory)
{
  this->impl = cpu;
  this->mMemory = memory;

  addImpl(21, new FactoryItem<CommandImplRead>());
}

void CommandFactory::addImpl(int code, FactoryItemInterface *impl)
{
  mCommands.insert(code, impl);
}

AbstactCommand *CommandFactory::createCommand(int code)
{
  FactoryItemInterface *cmd = mCommands.value(code, NULL);
  if(cmd) {
    return cmd->create(this->impl, this->mMemory);
  }
  return NULL;
}
