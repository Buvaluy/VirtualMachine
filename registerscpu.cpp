#include "registerscpu.h"

RegistersCPU::RegistersCPU()
{
    R0 = "000000";
    R1 = "000000";
    R2 = "000000";
    R3 = "000000";
    R4 = "000000";
    R5 = "000000";
    R6 = "000000";
    R7 = "000000";
    R8 = "000000";
    R9 = "000000";
}

QString RegistersCPU::getR0() const
{
    return R0;
}

void RegistersCPU::setR0(const QString &value)
{
    assert(value.toInt() <= 199999);
    R0 = value;
}

QString RegistersCPU::getR1() const
{
    return R1;
}

void RegistersCPU::setR1(const QString &value)
{
    assert(value.toInt() <= 199999);
    R1 = value;
}

QString RegistersCPU::getR2() const
{
    return R2;
}

void RegistersCPU::setR2(const QString &value)
{
    assert(value.toInt() <= 199999);
    R2 = value;
}

QString RegistersCPU::getR3() const
{
    return R3;
}

void RegistersCPU::setR3(const QString &value)
{
    assert(value.toInt() <= 199999);
    R3 = value;
}

QString RegistersCPU::getR4() const
{
    return R4;
}

void RegistersCPU::setR4(const QString &value)
{
    assert(value.toInt() <= 199999);
    R4 = value;
}

QString RegistersCPU::getR5() const
{
    return R5;
}

void RegistersCPU::setR5(const QString &value)
{
    assert(value.toInt() <= 199999);
    R5 = value;
}

QString RegistersCPU::getR6() const
{
    return R6;
}

void RegistersCPU::setR6(const QString &value)
{
    assert(value.toInt() <= 199999);
    R6 = value;
}

QString RegistersCPU::getR7() const
{
    return R7;
}

void RegistersCPU::setR7(const QString &value)
{
    assert(value.toInt() <= 199999);
    R7 = value;
}

QString RegistersCPU::getR8() const
{
    return R8;
}

void RegistersCPU::setR8(const QString &value)
{
    assert(value.toInt() <= 199999);
    R8 = value;
}

QString RegistersCPU::getR9() const
{
    return R9;
}

void RegistersCPU::setR9(const QString &value)
{
    assert(value.toInt() <= 199999);
    R9 = value;
}

