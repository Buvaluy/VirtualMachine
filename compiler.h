#ifndef COMPILER_H
#define COMPILER_H

#include "memory.h"
#include "codegenerator.h"

#include <QString>
#include <QMap>

class Compiler
{
protected:
  Memory *mMemory;
  CodeGenerator *mGenCode;
public:
  Compiler(Memory *mem);
  ~Compiler();

  QString parseLabel(QString &strSource);

  void checkCommand(QString &strSource);

  void exec(QString &strSource);

  QString getAddresType(QString str);
};

#endif // COMPILER_H
