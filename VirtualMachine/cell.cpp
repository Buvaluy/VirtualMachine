#include "cell.h"

Cell::Cell(QString value)
{
    cell = value;
}

QString Cell::getCell() const
{
    return cell;
}

void Cell::setCell(const QString &value)
{
    if(value.toInt() > 999999){ // В памяти могут быть и команды и данные. Если число то первые знак '0'/'1'
                                 //но если команда то первая может быть '0'/'1'/'2'
                                 //надо это будет доделать
        throw "SetCell " + value;
    }
    cell = value;
}

void Cell::setCell(const int &value)
{
    if(value > 999999){ // В памяти могут быть и команды и данные. Если число то первые знак '0'/'1'
                                 //но если команда то первая может быть '0'/'1'/'2'
                                 //надо это будет доделать
        throw "SetCell " + value;
    }
    cell = QString::number(value);
}
