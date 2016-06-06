#ifndef COMPILER_H
#define COMPILER_H

#include "memory.h"
#include "codegenerator.h"

#include <QString>
#include <QMap>
#include <QTextEdit>
#include <QProgressBar>
#include "abstactcommand.h"
#include "gui/debugpanel.h"
#include "commandfactory.h"

class Compiler
{
protected:
  Memory *mMemory;
  CodeGenerator *mGenCode;
  QTextEdit *out;
  DebugPanel *mDpanel;
  QProgressBar *mBar;
  CommandFactory *mFactory;
public:
  Compiler(Memory *mem, DebugPanel *panel, QProgressBar *mBar, CommandFactory *factory);
  ~Compiler();

  void setOutPutConsole(QTextEdit *ptr);

  QString parseLabel(QString &strSource);

  bool checkCommand(QString &strSource);

  void exec(QString &strSource);

  QString getAddresType(QString str);

  void getAddresCode(QString &strArg, QString &typeAdrr);

private:
  QString formatTime(QString str, int cnt);
  int indexCheckCommand;
};

#endif // COMPILER_H
