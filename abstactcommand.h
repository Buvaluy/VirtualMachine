#ifndef ABSTACTCOMMAND_H
#define ABSTACTCOMMAND_H

#include <QString>
#include "cpu.h"
#include "memory.h"

class AbstactCommand
{
private:
  QString name;
  QString code;
  QString arg;
  QString typeAddr;
protected:
  CPU *mCpu;
  Memory *mMemory;
  int currentMicroCmd;
  QStringList listMicroCommand;
public:
  AbstactCommand();

  virtual ~AbstactCommand() {}

  bool execute (QString strArg = "", QString typeAddr = "");

  virtual void straight(QString strArg); // Прямая
  virtual void straightRegister(QString strArg);// Прямая регистровая
  virtual void direct(QString strArg); //Непосредственная
  virtual void indirect(QString strArg);// Косвенная
  virtual void relative(QString strArg); //Относительная
  virtual void indirectRegister(QString strArg);//Косвенно-регистровая
  virtual void indexWithPostincrementRegister(QString strArg);//Индексная с постинкрементом
  virtual void indexWithPreddekrementomRegister(QString strArg);//Индексная с преддекрементом

  virtual void straightMC(QString strArg, int currentMicroCommand); // Прямая
  virtual void straightRegisterMC(QString strArg, int currentMicroCommand);// Прямая регистровая
  virtual void directMC(QString strArg, int currentMicroCommand); //Непосредственная
  virtual void indirectMC(QString strArg, int currentMicroCommand);// Косвенная
  virtual void relativeMC(QString strArg, int currentMicroCommand); //Относительная
  virtual void indirectRegisterMC(QString strArg, int currentMicroCommand);//Косвенно-регистровая
  virtual void indexWithPostincrementRegisterMC(QString strArg, int currentMicroCommand);//Индексная с постинкрементом
  virtual void indexWithPreddekrementomRegisterMC(QString strArg, int currentMicroCommand);//Индексная с преддекрементом

  //virtual QStringList getMicroCommandList();

  // return  true if finish
  // false if have command for run
  virtual bool executeMicroCommand(QString arg, QString addr, int currentMicroCommand);

  QString getName() const;
  void setName(const QString &value);

  QString getCode() const;
  void setCode(const QString &value);

  QString getArg() const;
  void setArg(const QString &value);

  QString getTypeAddr() const;
  void setTypeAddr(const QString &value);

  CPU *getCpu() const;
  void setCpu(CPU *cpu);

  void setMemory(Memory *memory);

  void push3Times0(QString &str);
  void push6Times0(QString &str);
  QStringList getListMicroCommand() const;

  void duplicateMicroCommand(int currentMicroCommand);
};

#endif // ABSTACTCOMMAND_H
