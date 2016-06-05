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

class CommandImplJmp : public AbstactCommand
{
public:

    CommandImplJmp(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplJz : public AbstactCommand
{
public:

    CommandImplJz(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplJnz : public AbstactCommand
{
public:

    CommandImplJnz(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplJs : public AbstactCommand
{
public:

    CommandImplJs(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplJns : public AbstactCommand
{
public:

    CommandImplJns(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplJo : public AbstactCommand
{
public:

    CommandImplJo(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplJno : public AbstactCommand
{
public:

    CommandImplJno(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplJrnz : public AbstactCommand
{
public:

    CommandImplJrnz(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplPush : public AbstactCommand
{
public:

    CommandImplPush(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplPop : public AbstactCommand
{
public:

    CommandImplPop(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplCall : public AbstactCommand
{
public:

    CommandImplCall(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplRet : public AbstactCommand
{
public:

    CommandImplRet(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};


#endif // COMMANDSIMPL_H
