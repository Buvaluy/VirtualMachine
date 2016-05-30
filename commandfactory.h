#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <QMap>
#include "abstactcommand.h"

class FactoryItemInterface {
public:
  virtual AbstactCommand * create(CPU *cpu, Memory *memory) = 0;
};

template<typename TClass>
class FactoryItem : public FactoryItemInterface {
  AbstactCommand * create(CPU *cpu, Memory *memory) override {
    return new TClass(cpu, memory);
  }
};

class CommandFactory
{
private:
  CPU *impl;
  Memory *mMemory;
  QMap<int, FactoryItemInterface *> mCommands;
public:
  CommandFactory(CPU *cpu, Memory *memory);

  void addImpl(int code, FactoryItemInterface *impl);
  AbstactCommand *createCommand(int code);
};

#endif // COMMANDFACTORY_H
