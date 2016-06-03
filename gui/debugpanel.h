#ifndef DEBUGPANEL_H
#define DEBUGPANEL_H

#include <QWidget>

namespace Ui {
class DebugPanel;
}

class DebugPanel : public QWidget
{
  Q_OBJECT

public:
  explicit DebugPanel(QWidget *parent = 0);
  ~DebugPanel();

  void updateCode(QStringList lCommand);

  void resetCurrentCommand();
  void nextStep();
private:
  Ui::DebugPanel *ui;
  int currentCommand = 0;
  QStringList mComands;

protected:
  void initializeHeadr(int rowCount);
};

#endif // DEBUGPANEL_H
