#include "memory.h"

Memory::Memory()
{
    for(int i = 0; i <=999; i++){
        memory.append(new Cell());
    }
}

const QString Memory::get(const int address)
{
    if(address > 999 || address < 0){
        throw "Get address " + address;
    }
    Cell *cell = memory.at(address);
    return cell->getCell();
}

void Memory::set(const int address, const QString &value)
{
    if(address > 999 || address < 0){
        throw "Set address " + address;
    }
    memory.at(address)->setCell(value);
}

void Memory::set(const int address, const int &value)
{
    if(address > 999 || address < 0){
        throw "Set address " + address;
    }
    memory.at(address)->setCell(value);
}
