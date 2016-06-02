#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  mMemory = new Memory();
  impl = new CPU();
  hightLighter = new HightLighter(ui->textEdit->document());
  cpuWidget = new CpuWidget(impl);
  ui->cpuWidgetLayout->addWidget(cpuWidget);
  impl->setCPUWidget(cpuWidget);
  mWdgt = new MemmoryWidget(mMemory);
  ui->memLyt->addWidget(mWdgt);
  mFactory = new CommandFactory(impl, mMemory);
  mRuner = new Runer(impl, mMemory, mFactory);
}

MainWindow::~MainWindow()
{
  delete impl;
  delete mFactory;
  delete hightLighter;
  delete mRuner;
  delete ui;
}

void MainWindow::on_actionCompiler_triggered()
{
  ui->tabWidget->setCurrentIndex(1);
  QString strSourse = ui->textEdit->document()->toPlainText();
  impl->clearCPU();
  impl->updateGUI();
  Compiler mComp(mMemory);
  mComp.setOutPutConsole(ui->consoleOut);
  mComp.exec(strSourse);
}

void MainWindow::on_actionNext_triggered()
{
  mRuner->nextStep();
}
