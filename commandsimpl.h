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
    // Все методы дял регистров

    void indirectRegister(QString arg) override {

    }

    void straightRegister(QString arg) override {

    }

    void indexWithPostincrementRegister(QString arg) override {

    }

    void indexWithPreddekrementomRegister(QString arg) override {

    }
};





#endif // COMMANDSIMPL_H
