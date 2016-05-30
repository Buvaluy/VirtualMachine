#ifndef CPU_H
#define CPU_H

#include "registerscpu.h"

class CPU : public RegistersCPU
{
protected:
    CPU();
public:
    int convertRegToInt(QString regValue);
    QString convertIntToReg(int value);

    QString getACC() const;
    void setACC(const QString &value);

    QString getDR() const;
    void setDR(const QString &value);

    QString getRDR() const;
    void setRDR(const QString &value);

    QString getRAR() const;
    void setRAR(const QString &value);

    QString getMDR() const;
    void setMDR(const QString &value);

    QString getMAR() const;
    void setMAR(const QString &value);

    QString getIR() const;
    void setIR(const QString &value);

    QString getOR() const;
    void setOR(const QString &value);

    QString getCOP() const;
    void setCOP(const QString &value);

    QString getTA() const;
    void setTA(const QString &value);

    QString getADR() const;
    void setADR(const QString &value);

    QString getRA() const;
    void setRA(const QString &value);

    QString getRB() const;
    void setRB(const QString &value);

    QString getSP() const;
    void setSP(const QString &value);

    QString getPC() const;
    void setPC(const QString &value);

    QString getI() const;
    void setI(const QString &value);

    QString getOV() const;
    void setOV(const QString &value);

    QString getS() const;
    void setS(const QString &value);

    QString getZ() const;
    void setZ(const QString &value);

private:
    // ALU
    QString ACC; //аккамулятор
    QString DR; //регистр данных АЛУ ( второй операнд)

    // POH
    QString RDR; //регистр данных
    QString RAR; //регистр адресса

    // RAM
    QString MDR; //регистр данных ОЗУ
    QString MAR; //регистр адресса ОЗУ

    // in.out
    QString IR; //входной регистр
    QString OR; //выходной регистр

    // CR
    QString COP; //код операции
    QString TA; //тип адресации
    QString ADR; //адресс или непосредственный операнд

    // register address
    QString RA; //регистр адресса при косвенной адресации
    QString RB; //регистр базового адреса
    QString SP; //указатель стека, адрес верхушки стека
    QString PC; //счетчик адреса команды ( текущая команда)

    // flags
    QString I; //флаг разрешения прерываний
    QString OV; //флаг переполнения
    QString S; //флаг отрицательного значения Acc
    QString Z; //флаг нулевого значения Acc

};

#endif // CPU_H
