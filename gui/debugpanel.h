#ifndef DEBUGPANEL_H
#define DEBUGPANEL_H

#include <QWidget>
#include "cpu.h"

namespace Ui {
class DebugPanel;
}

class DebugPanel : public QWidget
{
  Q_OBJECT

public:
  explicit DebugPanel(CPU* cpu, QWidget *parent = 0);
  ~DebugPanel();

  void updateCode(QStringList lCommand);

  void resetCurrentCommand();
  void nextStep();
private:
  Ui::DebugPanel *ui;
  int currentCommand = 0;
  QStringList mComands;
  CPU *mCpu;
protected:
  void initializeHeadr(int rowCount);
};

#endif // DEBUGPANEL_H
