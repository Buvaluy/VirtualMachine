#include "debugpanel.h"
#include "ui_debugpanel.h"

DebugPanel::DebugPanel(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DebugPanel)
{
  ui->setupUi(this);
  ui->tableWidget->clear();
}

DebugPanel::~DebugPanel()
{
  delete ui;
}

void DebugPanel::updateCode(QStringList lCommand)
{
  if(lCommand.size() == 0) return;
  mComands = lCommand;
  ui->tableWidget->blockSignals(true);
  initializeHeadr(lCommand.size());

  for(int r = 0; r < lCommand.size(); r ++) {
    ui->tableWidget->setItem(r, 0, new QTableWidgetItem(" "));
    ui->tableWidget->setItem(r, 1, new QTableWidgetItem(QString::number(r)));
    ui->tableWidget->setItem(r, 2, new QTableWidgetItem(lCommand.at(r)));
  }
  ui->tableWidget->setItem(currentCommand, 0, new QTableWidgetItem("->"));

  ui->tableWidget->blockSignals(false);
}

void DebugPanel::resetCurrentCommand()
{
  currentCommand = 0;
  updateCode(mComands);
}

void DebugPanel::nextStep()
{
  currentCommand ++;
  updateCode(mComands);
}

void DebugPanel::initializeHeadr(int rowCount)
{
  ui->tableWidget->clear();
  ui->tableWidget->verticalHeader()->setVisible(false);

  ui->tableWidget->setColumnCount(3);
  ui->tableWidget->setRowCount(rowCount);

  ui->tableWidget->setColumnWidth(0, 20);
  ui->tableWidget->setColumnWidth(1, 50);
  ui->tableWidget->setColumnWidth(2, (ui->tableWidget->width() - 100));

  ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("IP"));
  ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Адрес"));
  ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Комманда"));
}
