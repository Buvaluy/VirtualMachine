#ifndef MEMORY_H
#define MEMORY_H

#include "cell.h"
#include <QList>

class MemmoryWidget;

class Memory
{
public:
    Memory();

    const QString get(const int address);
    void set(const int address, const QString &value);
    void set(const int address, const int &value);

    void setGUIWidget(MemmoryWidget *wdgt);
    void updateGUI();

    void clear();
private:
    MemmoryWidget *wdgt;
    QList<Cell*> cells;
};

#endif // MEMORY_H
