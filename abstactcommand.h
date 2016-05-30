#ifndef ABSTACTCOMMAND_H
#define ABSTACTCOMMAND_H

#include <QString>
#include "cpu.h"

class AbstactCommand
{
private:
  QString name;
  QString code;
  QString arg;
  QString typeAddr;

protected:
  CPU *mCpu;

public:
  AbstactCommand();

  virtual bool execute (QString strArg = "", QString typeAddr = "") = 0;

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
};

#endif // ABSTACTCOMMAND_H
