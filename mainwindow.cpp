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
  mProgressBar->setStyleSheet("QProgressBar {border: 1px solid rgb(83, 83, 83);background-color: rgb(38, 40, 41);border-radius: 5px;} QProgressBar::chunk {background-color: rgb(64, 66, 68);width: 20px; }");
  mProgressBar->setMaximumSize(300, 20);
  mProgressBar->setMinimumSize(300, 20);
  mProgressBar->setFormat("");
  ui->statusBar->addWidget(mProgressBar);
  initializeGui();
  autoLoad();
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
  autoSave();
  QString strSourse = mCodeEdit->document()->toPlainText();
  mCpu->clearCPU();
  mCpu->clearRegister();
  mCpu->updateGUI();
  try{
    Compiler mComp(mMemory, mDpanel, mProgressBar);
    mComp.setOutPutConsole(ui->consoleOut);
    mComp.exec(strSourse);
    ui->stackedWidget->setCurrentIndex(1);
    ui->btnNext->setEnabled(true);
    ui->btnRun->setEnabled(true);
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
}

void MainWindow::autoSave()
{
  QFile file(autoLoadFileName);
  if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream stream(&file);
    stream << mCodeEdit->document()->toPlainText();
  }
  file.close();
}

void MainWindow::autoLoad()
{
  QFile file(autoLoadFileName);
  if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream stream(&file);
    mCodeEdit->clear();
    mCodeEdit->appendPlainText(stream.readAll());
  }
  file.close();
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

void MainWindow::on_btnCode_clicked()
{
  ui->btnCode->setChecked(true);
  ui->btnDebug->setChecked(false);
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnDebug_clicked()
{
  ui->btnCode->setChecked(false);
  ui->btnDebug->setChecked(true);
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnCompile_clicked()
{
  on_actionCompiler_triggered();
}

void MainWindow::on_btnRun_clicked()
{
  mRuner->run();
}

void MainWindow::on_btnNext_clicked()
{
  mRuner->nextStep();
}
