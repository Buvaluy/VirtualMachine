#ifndef CELL_H
#define CELL_H

#include <QString>

class Cell
{
public:
    Cell(QString value = "000000");

    QString getCell() const;
    void setCell(const QString &value);
    void setCell(const int &value);

private:
    QString cell;
};

#endif // CELL_H
