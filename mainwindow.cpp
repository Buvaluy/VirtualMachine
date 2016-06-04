#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>

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
  mDpanel = new DebugPanel(impl);
  mRuner = new Runer(impl, mMemory, mFactory, mDpanel);
  ui->vlDebug->addWidget(mDpanel);
  initializeGui();
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
  Compiler mComp(mMemory, mDpanel);
  mComp.setOutPutConsole(ui->consoleOut);
  mComp.exec(strSourse);
}

void MainWindow::on_actionNext_triggered()
{
  mRuner->nextStep();
}

void MainWindow::on_actionOpen_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   QDir::currentPath(),
                                                   tr("Code (*.asm)"));
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QTextStream stream(&file);
      ui->textEdit->clear();
      ui->textEdit->append(stream.readAll());
    }
    file.close();
  }
}

void MainWindow::on_actionSave_triggered()
{

  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                             QDir::currentPath(),
                             tr("Code (*.asm)"));
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream stream(&file);
      stream << ui->textEdit->document()->toPlainText();
    }
    file.close();
  }
}

void MainWindow::initializeGui()
{
  ui->tabDevise->setTabText(0, "устройства");
  ui->tabDevise->setTabText(1, "микрокоманд");
  ui->tabDevise->setTabText(2, "кеш");
}

void MainWindow::on_actionRun_triggered()
{
    mDpanel->resetCurrentCommand();
}

void MainWindow::on_actionReset_triggered()
{
  mDpanel->resetCurrentCommand();
  impl->clearCPU();
}
