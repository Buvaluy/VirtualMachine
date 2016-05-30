#include "cpu.h"

CPU::CPU()
{
    ACC = "000000";
    DR = "000000";
    RDR = "000000";
    RAR = "0";
    MDR = "000000";
    MAR = "000";
    IR = "000000";
    OR = "000000";
    COP = "00";
    TA = "0";
    ADR = "000";
    SP = "000";
    PC = "000";
    RA = "000";
    RB = "000";
    I = "0";
    OV = "0";
    S = "0";
    Z = "1";
}

int CPU::convertRegToInt(QString regValue)
{
  QChar flg = regValue.at(0);
  regValue = regValue.remove(0, 1);
  int rVal = regValue.toInt();
  if(flg == '1') {
    rVal *= -1;
  }
  return rVal;
}

QString CPU::convertIntToReg(int value)
{
  // TODO impl method
}

QString CPU::getACC() const
{
    return ACC;
}

void CPU::setACC(const QString &value)
{
    if(value.toInt() == 0){ //проверка на 0
        setZ("1"); //флаг нуля
        setS("0"); //флаг отрицательного значения
        setOV("0"); //флаг переполнения
        ACC = "000000";
        return;
    }else{
        setZ("0");
    }
    if(value.toInt() >= 200000){ //проверка на переполнение
        setOV("1");
        ACC = "000000";
        setZ("0");
        setS("0");
        return;
    }
    if(value.at(0) == '1'){ //проверка на отрицательное число
        setS("1");
    }else{
        setS("0");
    }
    ACC = value;
}

QString CPU::getRDR() const
{
    return RDR;
}

void CPU::setRDR(const QString &value)
{
    RDR = value;
}

QString CPU::getRAR() const
{
    return RAR;
}

void CPU::setRAR(const QString &value)
{
    RAR = value;
}

QString CPU::getMDR() const
{
    return MDR;
}

void CPU::setMDR(const QString &value)
{
    //разбиение MDR на регитры для CR
    MDR = value;
    int str = value.at(0).digitValue() + value.at(1).digitValue();
    setCOP(QString::number(str));
    setTA(value.at(2));
    str = value.at(3).digitValue() + value.at(4).digitValue() + value.at(5).digitValue();
    setADR(QString::number(str));
    //установим MAR
    setMAR(ADR);
}

QString CPU::getMAR() const
{
    return MAR;
}

void CPU::setMAR(const QString &value)
{
    assert(value.toInt() <= 999);
    MAR = value;
}

QString CPU::getIR() const
{
    return IR;
}

void CPU::setIR(const QString &value)
{
    setACC(value);//все проверки в ACC уже есть
    IR = value;//или же прировнять IR = ACC
}

QString CPU::getOR() const
{
    return OR;
}

void CPU::setOR(const QString &value)
{
    OR = value;
}

QString CPU::getCOP() const
{
    return COP;
}

void CPU::setCOP(const QString &value)
{
    assert(value.toInt() <= 99);
    COP = value;
}

QString CPU::getTA() const
{
    return TA;
}

void CPU::setTA(const QString &value)
{
    assert(value.toInt() <= 9);
    TA = value;
}

QString CPU::getADR() const
{
    return ADR;
}

void CPU::setADR(const QString &value)
{
    assert(value.toInt() <= 999);
    ADR = value;
}

QString CPU::getRA() const
{
    return RA;
}

void CPU::setRA(const QString &value)
{
    assert(value.toInt() <= 999);
    RA = value;
}

QString CPU::getRB() const
{
    return RB;
}

void CPU::setRB(const QString &value)
{
    assert(value.toInt() <= 999);
    RB = value;
}

QString CPU::getSP() const
{
    return SP;
}

void CPU::setSP(const QString &value)
{
    assert(value.toInt() <= 999);
    SP = value;
}

QString CPU::getPC() const
{
    return PC;
}

void CPU::setPC(const QString &value)
{
    assert(value.toInt() <= 999);
    PC = value;
}

QString CPU::getI() const
{
    return I;
}

void CPU::setI(const QString &value)
{
    assert(value.toInt() <= 1);
    I = value;
}

QString CPU::getOV() const
{
    return OV;
}

void CPU::setOV(const QString &value)
{
    assert(value.toInt() <= 1);
    OV = value;
}

QString CPU::getS() const
{
    return S;
}

void CPU::setS(const QString &value)
{
    assert(value.toInt() <= 1);
    S = value;
}

QString CPU::getZ() const
{
    return Z;
}

void CPU::setZ(const QString &value)
{
    assert(value.toInt() <= 1);
    Z = value;
}

QString CPU::getDR() const
{
    return DR;
}

void CPU::setDR(const QString &value)
{
    DR = value;
}
