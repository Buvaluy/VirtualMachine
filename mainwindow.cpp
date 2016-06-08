#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QException>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  mMemory = new Memory();
  mCpu = new CPU();
  mCodeEdit = new CodeEditor();
  mCodeEdit->setStyleSheet("font: 16px consolas;");
  ui->vltextEdit->addWidget(mCodeEdit);
  mHightLighter = new HightLighter(mCodeEdit->document());
  mCpuWidget = new CpuWidget(mCpu);
  ui->cpuWidgetLayout->addWidget(mCpuWidget);
  mCpu->setCPUWidget(mCpuWidget);
  mWdgt = new MemmoryWidget(mMemory);
  ui->memLyt->addWidget(mWdgt);
  mFactory = new CommandFactory(mCpu, mMemory);
  mDpanel = new DebugPanel(mCpu);
  mRuner = new Runer(mCpu, mMemory, mFactory, mDpanel);
  ui->vlDebug->addWidget(mDpanel);
  mProgressBar = new QProgressBar();
  mProgressBar->setMaximumSize(250, 20);
  mProgressBar->setFormat("");
  ui->statusBar->addWidget(mProgressBar);

  initializeGui();


}

MainWindow::~MainWindow()
{
  delete mCpu;
  delete mFactory;
  delete mHightLighter;
  delete mCodeEdit;
  delete mRuner;
  delete ui;
}

void MainWindow::on_actionCompiler_triggered()
{
  ui->tabWidget->setCurrentIndex(1);
  QString strSourse = mCodeEdit->document()->toPlainText();
  mCpu->clearCPU();
  mCpu->clearRegister();
  mCpu->updateGUI();
  try{
    Compiler mComp(mMemory, mDpanel, mProgressBar);
    mComp.setOutPutConsole(ui->consoleOut);
    mComp.exec(strSourse);
  } catch(QException &exp) {
    qDebug() << exp.what();
  }
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
      mCodeEdit->clear();
      mCodeEdit->appendPlainText(stream.readAll());
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
      stream << mCodeEdit->document()->toPlainText();
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
  mCpu->clearCPU();
  mCpu->clearRegister();
  mDpanel->resetCurrentCommand();
}

void MainWindow::on_actionResetMemmory_triggered()
{
  mMemory->clear();
}

void MainWindow::on_actionSaveMemory_triggered()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                             QDir::currentPath(),
                             tr("Memory (*.mem)"));
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream stream(&file);
      for(int i = 0; i < 1000; i ++) {
        stream << mMemory->get(i);
      }
    }
    file.close();
  }
}

void MainWindow::on_actionLoadMemory_triggered()
{
  QString strBuffer;
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   QDir::currentPath(),
                                                   tr("Memory (*.mem)"));
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QTextStream stream(&file);
      for(int i = 0; i < 1000; i ++) {
        stream >> strBuffer;
        mMemory->set(i, strBuffer);
      }
    }
    file.close();
  }
}

void MainWindow::on_actionDeveloper_triggered()
{
  QMessageBox::about(NULL, "Разработчики", "Борисов Дмитрий Юрьевич\nШульга Александр Евгеньевич");
}

void MainWindow::on_actionVersion_triggered()
{
  QMessageBox::about(NULL, "Версия", "Альфа версия 1.00.\n build 122");
}
