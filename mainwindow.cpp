#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  hightLighter = new HightLighter(ui->textEdit->document());
  cpuWidget = new CpuWidget();
  ui->cpuWidgetLayout->addWidget(cpuWidget);
  //cpuWidget->show();
}

MainWindow::~MainWindow()
{
  //delete cpuWidget;
  delete hightLighter;
  delete ui;
}
