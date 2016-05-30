#ifndef REGISTERSCPU_H
#define REGISTERSCPU_H
#include <QString>
#include <assert.h>
#include <QObject>

class RegistersCPU : public QObject
{
  Q_OBJECT

public:
    RegistersCPU();

public:
    QString getR0() const;

    void setR0(const QString &value);

    QString getR1() const;

    void setR1(const QString &value);

    QString getR2() const;

    void setR2(const QString &value);

    QString getR3() const;

    void setR3(const QString &value);

    QString getR4() const;

    void setR4(const QString &value);

    QString getR5() const;

    void setR5(const QString &value);

    QString getR6() const;

    void setR6(const QString &value);

    QString getR7() const;

    void setR7(const QString &value);

    QString getR8() const;

    void setR8(const QString &value);

    QString getR9() const;

    void setR9(const QString &value);

private:
    QString R0;
    QString R1;
    QString R2;
    QString R3;
    QString R4;
    QString R5;
    QString R6;
    QString R7;
    QString R8;
    QString R9;
};

#endif // REGISTERSCPU_H
