#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/hightlighter.h"
#include "gui/cpuwidget.h"
#include "gui/memmorywidget.h"
#include "gui/microcommandview.h"

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

  enum RightTab { Devise, MicroCommand ,Cache };

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

  void on_actionResetMemmory_triggered();

  void on_actionSaveMemory_triggered();

  void on_actionLoadMemory_triggered();

  void on_actionDeveloper_triggered();

  void on_actionVersion_triggered();

  void on_btnCode_clicked();

  void on_btnDebug_clicked();

  void on_btnCompile_clicked();

  void on_btnRun_clicked();

  void on_btnNext_clicked();

  void on_tabDevise_tabBarClicked(int index);

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
  MicroCommandView *mMcmdView;

  const QString autoLoadFileName = "autosave.asm";
  bool mIsMicroCmdOn = false;
protected:
  void initializeGui();

  void autoSave();
  void autoLoad();
};

#endif // MAINWINDOW_H
