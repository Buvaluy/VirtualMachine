#include "microcommandview.h"
#include "ui_microcommandview.h"

#include <QDebug>

MicroCommandView::MicroCommandView(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MicroCommandView)
{
  ui->setupUi(this);
}

MicroCommandView::~MicroCommandView()
{
  delete ui;
}

void MicroCommandView::updateGui(QStringList microCommandList, int currentMicroCommand)
{
  initializeTableHeadr(microCommandList.size());

  for(int i = 0; i < microCommandList.size(); i ++) {
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(" "));
    ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(i)));
    ui->tableWidget->setItem(i, 2, new QTableWidgetItem(microCommandList.at(i)));
  }

  ui->tableWidget->setItem(currentMicroCommand, 0, new QTableWidgetItem(">"));
}

void MicroCommandView::initializeTableHeadr(int countRow)
{
  ui->tableWidget->clear();

  ui->tableWidget->setColumnCount(3);
  ui->tableWidget->setRowCount(countRow);

  ui->tableWidget->setColumnWidth(0, 20);
  ui->tableWidget->setColumnWidth(1, 40);
  ui->tableWidget->setColumnWidth(2, ui->tableWidget->width() - 80);

  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

  ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("*"));
  ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("№"));
  ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Название"));
}
