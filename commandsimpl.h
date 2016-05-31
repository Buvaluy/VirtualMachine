#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H

#include "cpu.h"
#include "abstactcommand.h"

class CommandImplRead : public AbstactCommand
{
public:

    CommandImplRead(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    bool execute(QString strArg, QString addrType) override;
};


class CommandImplWrite : public AbstactCommand
{
public:

    CommandImplWrite(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    bool execute(QString strArg, QString addrType) override;
};


class CommandImplAdd : public AbstactCommand
{
public:

    CommandImplAdd(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    bool execute(QString strArg, QString addrType) override;
};


class CommandImplSub : public AbstactCommand
{
public:

    CommandImplSub(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    bool execute(QString strArg, QString addrType) override;
};


class CommandImplMul : public AbstactCommand
{
public:

    CommandImplMul(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    bool execute(QString strArg, QString addrType) override;
};


class CommandImplDiv : public AbstactCommand
{
public:

    CommandImplDiv(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    bool execute(QString strArg, QString addrType) override;
};



#endif // COMMANDSIMPL_H
