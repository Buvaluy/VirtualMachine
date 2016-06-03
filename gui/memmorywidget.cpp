#include "memmorywidget.h"
#include "ui_memmorywidget.h"

#include <QDebug>


MemmoryWidget::MemmoryWidget(Memory *memory, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MemmoryWidget)
{
  this->memory = memory;
  memory->setGUIWidget(this);
  ui->setupUi(this);
  updateGUI();
}

MemmoryWidget::~MemmoryWidget()
{
  delete ui;
}

void MemmoryWidget::updateGUI()
{
  ui->tableMemory->blockSignals(true);

  ui->tableMemory->clear();
  ui->tableMemory->verticalHeader()->setVisible(true);
  ui->tableMemory->horizontalHeader()->setVisible(true);
  ui->tableMemory->setColumnCount(10);
  ui->tableMemory->setRowCount(100);
  ui->tableMemory->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  for(int k = 0; k < 10; k ++) {
    ui->tableMemory->setHorizontalHeaderItem(k, new QTableWidgetItem(QString::number(k)));
  }

  for(int k = 0; k < 100; k ++) {
    ui->tableMemory->setVerticalHeaderItem(k, new QTableWidgetItem(QString::number(k)));
  }

  int index = 0;
  for(int r = 0; r < 100; r ++) {
    for(int k = 0; k < 10; k ++, index ++) {
      ui->tableMemory->setItem(r, k, new QTableWidgetItem(memory->get(index)));
    }
  }

  ui->tableMemory->blockSignals(false);
}

void MemmoryWidget::on_tableMemory_itemChanged(QTableWidgetItem *item)
{
  QString strArg = item->text();
  while (strArg.size() < 6) {
   strArg.push_front("0");
  }
  int adr = item->row() * 10 + item->column();
  memory->set(adr, strArg);
}
