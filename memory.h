#ifndef MEMORY_H
#define MEMORY_H

#include "cell.h"
#include <QList>

class Memory : public Cell
{
public:
    Memory();
    const QString get(const int address);
    void set(const int address, const QString &value);
    void set(const int address, const int &value);

private:
    QList<Cell*> memory;
};

#endif // MEMORY_H
