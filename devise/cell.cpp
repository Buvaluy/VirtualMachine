#include "cell.h"

/*
 * Работа с ячейками памяти
 */
Cell::Cell(QString value)
{
    cell = value;
}

/*
 * Выходные данные: QString с данными ячейки ОЗУ
 */
QString Cell::getCell() const
{
    return cell;
}

/*
 * Запись данных в ячейку ОЗУ
 * - входнные данные: данные которые будут
 * записаны в ячейку озу
 */
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
