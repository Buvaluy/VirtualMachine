#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H

#include "cpu.h"
#include "abstactcommand.h"

class CommandImplIn : public AbstactCommand
{
public:

    CommandImplIn(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplOut : public AbstactCommand
{
public:

    CommandImplOut(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};



class CommandImplRead : public AbstactCommand
{
public:

    CommandImplRead(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void direct(QString arg) override;

    void indirect(QString arg) override;

    void straight(QString arg) override;
};

class CommandImplWrite : public AbstactCommand
{
public:

    CommandImplWrite(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void indirect(QString arg) override;

    void straight(QString arg) override;
};

class CommandImplAdd : public AbstactCommand
{
public:

    CommandImplAdd(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void direct(QString arg) override;

    void indirect(QString arg) override;

    void straight(QString arg) override;
};

class CommandImplSub : public AbstactCommand
{
public:

    CommandImplSub(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void direct(QString arg) override;

    void indirect(QString arg) override;

    void straight(QString arg) override;
};

class CommandImplMul : public AbstactCommand
{
public:

    CommandImplMul(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void direct(QString arg) override;

    void indirect(QString arg) override;

    void straight(QString arg) override;
};

class CommandImplDiv : public AbstactCommand
{
public:

    CommandImplDiv(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void direct(QString arg) override;

    void indirect(QString arg) override;

    void straight(QString arg) override;
};

class CommandImplReadRegister : public AbstactCommand
{
public:

    CommandImplReadRegister(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void indirectRegister(QString arg) override;

    void straightRegister(QString arg) override;

    void indexWithPostincrementRegister(QString arg) override;

    void indexWithPreddekrementomRegister(QString arg) override;
};


class CommandImplWriteRegister : public AbstactCommand
{
public:

    CommandImplWriteRegister(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void indirectRegister(QString arg) override;

    void straightRegister(QString arg) override;

    void indexWithPostincrementRegister(QString arg) override;

    void indexWithPreddekrementomRegister(QString arg) override;
};

class CommandImplAddRegister : public AbstactCommand
{
public:

    CommandImplAddRegister(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void indirectRegister(QString arg) override;

    void straightRegister(QString arg) override;

    void indexWithPostincrementRegister(QString arg) override;

    void indexWithPreddekrementomRegister(QString arg) override;
};

class CommandImplSubRegister : public AbstactCommand
{
public:

    CommandImplSubRegister(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void indirectRegister(QString arg) override;

    void straightRegister(QString arg) override;

    void indexWithPostincrementRegister(QString arg) override;

    void indexWithPreddekrementomRegister(QString arg) override;
};

class CommandImplMulRegister : public AbstactCommand
{
public:

    CommandImplMulRegister(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void indirectRegister(QString arg) override;

    void straightRegister(QString arg) override;

    void indexWithPostincrementRegister(QString arg) override;

    void indexWithPreddekrementomRegister(QString arg) override;
};

class CommandImplDivRegister : public AbstactCommand
{
public:

    CommandImplDivRegister(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void indirectRegister(QString arg) override;

    void straightRegister(QString arg) override;

    void indexWithPostincrementRegister(QString arg) override;

    void indexWithPreddekrementomRegister(QString arg) override;
};





#endif // COMMANDSIMPL_H
