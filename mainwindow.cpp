#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  hightLighter = new HightLighter(ui->textEdit->document());
}

MainWindow::~MainWindow()
{
  delete hightLighter;
  delete ui;
}
