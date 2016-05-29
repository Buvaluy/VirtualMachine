#ifndef ABSTACTCOMMAND_H
#define ABSTACTCOMMAND_H

#include <QString>

class AbstactCommand
{
private:
  QString name;
  QString code;
  QString arg;
  QString typeAddr;
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
};

#endif // ABSTACTCOMMAND_H
