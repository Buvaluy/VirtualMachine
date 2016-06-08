#ifndef COMPILER_H
#define COMPILER_H

#include "memory.h"
#include "codegenerator.h"

#include <QString>
#include <QMap>
#include <QTextEdit>
#include <QProgressBar>
#include "gui/debugpanel.h"

class Compiler
{
protected:
  Memory *mMemory;
  CodeGenerator *mGenCode;
  QTextEdit *out;
  DebugPanel *mDpanel;
  QProgressBar *mBar;
public:
  Compiler(Memory *mem, DebugPanel *panel, QProgressBar *mBar);
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
