#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <QMap>
#include "abstactcommand.h"
#include "cpu.h"

class FactoryItemInterface {
public:
  virtual AbstactCommand * create(CPU *cpu) = 0;
};

template<typename TClass>
class FactoryItem : public FactoryItemInterface {
  AbstactCommand * create(CPU *cpu) override {
    return new TClass(cpu);
  }
};

class CommandFactory
{
private:
  CPU *impl;
  QMap<int, FactoryItemInterface *> mCommands;
public:
  CommandFactory(CPU *cpu);

  AbstactCommand *createCommand(int code);
};

#endif // COMMANDFACTORY_H
