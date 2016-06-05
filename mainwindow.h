#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/hightlighter.h"
#include "gui/cpuwidget.h"
#include "gui/memmorywidget.h"

#include "memory.h"
#include "cpu.h"
#include "compiler.h"
#include "commandfactory.h"
#include "runer.h"
#include "gui/debugpanel.h"
#include "gui/codeeditor.h"

#include <QScopedPointer>
#include <QProgressBar>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionCompiler_triggered();

  void on_actionNext_triggered();

  void on_actionOpen_triggered();

  void on_actionSave_triggered();

  void on_actionRun_triggered();

  void on_actionReset_triggered();

protected:
  Ui::MainWindow *ui;
  Memory *mMemory;
  CPU *mCpu;
  HightLighter *mHightLighter;
  CpuWidget *mCpuWidget;
  MemmoryWidget *mWdgt;
  CommandFactory *mFactory;
  Runer *mRuner;
  DebugPanel *mDpanel;
  QProgressBar *mProgressBar;
  CodeEditor *mCodeEdit;
protected:
  void initializeGui();
};

#endif // MAINWINDOW_H
