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

#include <QScopedPointer>

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

private:
  Ui::MainWindow *ui;
  Memory *mMemory;
  CPU *impl;
  HightLighter *hightLighter;
  CpuWidget *cpuWidget;
  MemmoryWidget *mWdgt;
  CommandFactory *mFactory;
  Runer *mRuner;

  void initializeGui();
};

#endif // MAINWINDOW_H
