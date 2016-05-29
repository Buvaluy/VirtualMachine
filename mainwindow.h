#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/hightlighter.h"
#include "gui/cpuwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  HightLighter *hightLighter;
  CpuWidget *cpuWidget;
};

#endif // MAINWINDOW_H
