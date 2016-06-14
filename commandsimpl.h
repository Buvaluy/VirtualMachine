#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H

#include "cpu.h"
#include "abstactcommand.h"

class CommandImplIn : public AbstactCommand
{
public:
  ~CommandImplIn() override {}

  CommandImplIn(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
  void setMicroCommandList();
  void straightMC(QString arg, int currentMicroCommand) override;
};

class CommandImplOut : public AbstactCommand
{
public:
  ~CommandImplOut() override {}

  CommandImplOut(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
  void setMicroCommandList();
  void straightMC(QString arg, int currentMicroCommand) override;
};



class CommandImplRead : public AbstactCommand
{
public:
  ~CommandImplRead() override {}

  CommandImplRead(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void direct(QString arg) override;

  void indirect(QString arg) override;

  void straight(QString arg) override;

  void setMicroCommandList();

  void directMC(QString arg, int currentMicroCommand) override;

  void indirectMC(QString arg, int currentMicroCommand) override;

  void straightMC(QString arg, int currentMicroCommand) override;
};

class CommandImplWrite : public AbstactCommand
{
public:
  ~CommandImplWrite() override {}

  CommandImplWrite(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void indirect(QString arg) override;

  void straight(QString arg) override;

  void setMicroCommandList();

  void indirectMC(QString arg, int currentMicroCommand) override;

  void straightMC(QString arg, int currentMicroCommand) override;
};

class CommandImplAdd : public AbstactCommand
{
public:
  ~CommandImplAdd() override {}

  CommandImplAdd(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void direct(QString arg) override;

  void indirect(QString arg) override;

  void straight(QString arg) override;

  void setMicroCommandList();

  void directMC(QString arg, int currentMicroCommand) override;

  void indirectMC(QString arg, int currentMicroCommand) override;

  void straightMC(QString arg, int currentMicroCommand) override;
};

class CommandImplSub : public AbstactCommand
{
public:
  ~CommandImplSub() override {}

  CommandImplSub(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void direct(QString arg) override;

  void indirect(QString arg) override;

  void straight(QString arg) override;

  void setMicroCommandList();

  void directMC(QString arg, int currentMicroCommand) override;

  void indirectMC(QString arg, int currentMicroCommand) override;

  void straightMC(QString arg, int currentMicroCommand) override;
};

class CommandImplMul : public AbstactCommand
{
public:
  ~CommandImplMul() override {}

  CommandImplMul(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void direct(QString arg) override;

  void indirect(QString arg) override;

  void straight(QString arg) override;

  void setMicroCommandList();

  void directMC(QString arg, int currentMicroCommand) override;

  void indirectMC(QString arg, int currentMicroCommand) override;

  void straightMC(QString arg, int currentMicroCommand) override;
};

class CommandImplDiv : public AbstactCommand
{
public:
  ~CommandImplDiv() override {}

  CommandImplDiv(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void direct(QString arg) override;

  void indirect(QString arg) override;

  void straight(QString arg) override;

  void setMicroCommandList();

  void directMC(QString arg, int currentMicroCommand) override;

  void indirectMC(QString arg, int currentMicroCommand) override;

  void straightMC(QString arg, int currentMicroCommand) override;
};

class CommandImplReadRegister : public AbstactCommand
{
public:
  ~CommandImplReadRegister() override {}

  CommandImplReadRegister(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void indirectRegister(QString arg) override;

  void straightRegister(QString arg) override;

  void indexWithPostincrementRegister(QString arg) override;

  void indexWithPreddekrementomRegister(QString arg) override;

  void setMicroCommandList();

  void indirectRegisterMC(QString arg, int currentMicroCommand) override;

  void straightRegisterMC(QString arg, int currentMicroCommand) override;

  void indexWithPostincrementRegisterMC(QString arg, int currentMicroCommand) override;

  void indexWithPreddekrementomRegisterMC(QString arg, int currentMicroCommand) override;
};


class CommandImplWriteRegister : public AbstactCommand
{
public:
  ~CommandImplWriteRegister() override {}

  CommandImplWriteRegister(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void indirectRegister(QString arg) override;

  void straightRegister(QString arg) override;

  void indexWithPostincrementRegister(QString arg) override;

  void indexWithPreddekrementomRegister(QString arg) override;

  void setMicroCommandList();

  void indirectRegisterMC(QString arg, int currentMicroCommand) override;

  void straightRegisterMC(QString arg, int currentMicroCommand) override;

  void indexWithPostincrementRegisterMC(QString arg, int currentMicroCommand) override;

  void indexWithPreddekrementomRegisterMC(QString arg, int currentMicroCommand) override;
};

class CommandImplAddRegister : public AbstactCommand
{
public:
  ~CommandImplAddRegister() override {}

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
  ~CommandImplSubRegister() override {}

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
  ~CommandImplMulRegister() override {}

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
  ~CommandImplDivRegister() override {}

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
  ~CommandImplJmp() override {}

  CommandImplJmp(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};

class CommandImplJz : public AbstactCommand
{
public:
  ~CommandImplJz() override {}

  CommandImplJz(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};

class CommandImplJnz : public AbstactCommand
{
public:
  ~CommandImplJnz() override {}

  CommandImplJnz(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};

class CommandImplJs : public AbstactCommand
{
public:
  ~CommandImplJs() override {}

  CommandImplJs(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};

class CommandImplJns : public AbstactCommand
{
public:
  ~CommandImplJns() override {}

  CommandImplJns(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};

class CommandImplJo : public AbstactCommand
{
public:
  ~CommandImplJo() override {}

  CommandImplJo(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};

class CommandImplJno : public AbstactCommand
{
public:
  ~CommandImplJno() override {}

  CommandImplJno(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};

class CommandImplJrnz : public AbstactCommand
{
public:
  ~CommandImplJrnz() override {}

  CommandImplJrnz(CPU *cpu, Memory *memory) {
    setCpu(cpu);
    setMemory(memory);
  }

  void straight(QString arg) override;
};


class CommandImplPush : public AbstactCommand
{
public:
    ~CommandImplPush() override {}
    CommandImplPush(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplPop : public AbstactCommand
{
public:
    ~CommandImplPop() override {}
    CommandImplPop(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplCall : public AbstactCommand
{
public:
    ~CommandImplCall() override {}
    CommandImplCall(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg) override;
};

class CommandImplRet : public AbstactCommand
{
public:
    ~CommandImplRet() override {}
    CommandImplRet(CPU *cpu, Memory *memory) {
        setCpu(cpu);
        setMemory(memory);
    }

    void straight(QString arg = "") override;
};

#endif // COMMANDSIMPL_H
