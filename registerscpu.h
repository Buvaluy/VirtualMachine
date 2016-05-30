#ifndef REGISTERSCPU_H
#define REGISTERSCPU_H
#include <QString>
#include <QStringList>
#include <assert.h>
#include <QObject>

class RegistersCPU : public QObject
{
  Q_OBJECT

public:
    RegistersCPU();

public:
    void clearRegister();

    void setRegisterValue(int addr, QString value);
    QString getRegisterValue(int addr);

private:
    QStringList registers;
};

#endif // REGISTERSCPU_H
