#ifndef COMPILER_H
#define COMPILER_H

#include "memory.h"
#include "codegenerator.h"

#include <QString>
#include <QMap>
#include <QTextEdit>
#include "gui/debugpanel.h"

class Compiler
{
protected:
  Memory *mMemory;
  CodeGenerator *mGenCode;
  QTextEdit *out;
  DebugPanel *mDpanel;
public:
  Compiler(Memory *mem, DebugPanel *panel);
  ~Compiler();

  void setOutPutConsole(QTextEdit *ptr);

  QString parseLabel(QString &strSource);

  void checkCommand(QString &strSource);

  void exec(QString &strSource);

  QString getAddresType(QString str);

private:
  QString formatTime(QString str, int cnt);
};

#endif // COMPILER_H
