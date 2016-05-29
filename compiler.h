#ifndef COMPILER_H
#define COMPILER_H

#include <QString>
#include <QMap>

class Compiler
{
public:
  Compiler();

  QString parseLabel(QString &strSource);

};

#endif // COMPILER_H
