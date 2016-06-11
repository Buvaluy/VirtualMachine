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
//уставление данных в регистр CPU(R0-R9) по его номеру
void RegistersCPU::setRegisterValue(int addr, QString value)
{
  if(addr >= 0 && addr <= 9) {
     assert(value.toInt() <= 199999);
     registers.replace(addr, value);
  } else {
    //assert("Invalid addr value");
  }
}
//получение данных в регистр CPU(R0-R9) по его номеру
QString RegistersCPU::getRegisterValue(int addr)
{
  if(addr >= 0 && addr <= 9) {
     return registers.at(addr);
  }

  return "0";
}


