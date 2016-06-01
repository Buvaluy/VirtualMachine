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
public:
  AbstactCommand();

  bool execute (QString strArg = "", QString typeAddr = "");

  virtual void straight(QString strArg); // Прямая
  virtual void straightRegister(QString strArg);// Прямая регистровая
  virtual void direct(QString strArg); //Непосредственная
  virtual void indirect(QString strArg);// Косвенная
  virtual void relative(QString strArg); //Относительная
  virtual void indirectRegister(QString strArg);//Косвенно-регистровая
  virtual void indexWithPostincrementRegister(QString strArg);//Индексная с постинкрементом
  virtual void indexWithPreddekrementomRegister(QString strArg);//Индексная с преддекрементом

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
};

#endif // ABSTACTCOMMAND_H
