#include "memory.h"
#include "gui/memmorywidget.h"


Memory::Memory()
{
  clear();
}
//получение данных с ячейки ОЗУ по её номеру
const QString Memory::get(const int address)
{
    if(address > 999 || address < 0){
        throw "Get address " + address;
    }
    Cell *cell = cells.at(address);
    return cell->getCell();
}
//уставление данных в ячейку ОЗУ по её номеру
void Memory::set(const int address, const QString &value)
{
    if(address > 999 || address < 0){
        throw "Set address " + address;
    }
    cells.at(address)->setCell(value);
    updateGUI();
}
//уставление данных в ячейку ОЗУ по её номеру
void Memory::set(const int address, const int &value)
{
    if(address > 999 || address < 0){
        throw "Set address " + address;
    }
    cells.at(address)->setCell(value);
    updateGUI();
}

void Memory::setGUIWidget(MemmoryWidget *wdgt)
{
  this->wdgt = wdgt;
}

void Memory::updateGUI()
{
  this->wdgt->updateGUI();
}

void Memory::clear()
{
  cells.clear();
  for(int i = 0; i <=999; i++){
      cells.append(new Cell());
  }
}
