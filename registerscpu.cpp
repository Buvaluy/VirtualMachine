#include "registerscpu.h"

RegistersCPU::RegistersCPU()
{
  clearRegister();
}

void RegistersCPU::clearRegister()
{
  registers.clear();
  registers << "000000"
            << "000000"
            << "000000"
            << "000000"
            << "000000"
            << "000000"
            << "000000"
            << "000000"
            << "000000"
            << "000000";
}

void RegistersCPU::setRegisterValue(int addr, QString value)
{
  if(addr >= 0 && addr <= 9) {
     assert(value.toInt() <= 199999);
     registers.replace(addr, value);
  } else {
    //assert("Invalid addr value");
  }
}

QString RegistersCPU::getRegisterValue(int addr)
{
  if(addr >= 0 && addr <= 9) {
     return registers.at(addr);
  }

  return "0";
}


