#include "cpuwidget.h"
#include "ui_cpuwidget.h"

#include <QDebug>

CpuWidget::CpuWidget(CPU *cpu, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CpuWidget)
{
  ui->setupUi(this);
  impl = cpu;
  updateGUI();
}

CpuWidget::~CpuWidget()
{
  delete ui;
}

void CpuWidget::updateGUI()
{
  ui->textBoxAcc->setText(impl->getACC());
  ui->textBoxADR->setText(impl->getADR());
  ui->textBoxCOP->setText(impl->getCOP());
  ui->textBoxDR->setText(impl->getDR());
  ui->textBoxI->setText(impl->getI());
  ui->textBoxIR->setText(impl->getIR());
  ui->textBoxMAR->setText(impl->getMAR());
  ui->textBoxMDR->setText(impl->getMDR());
  ui->textBoxOR->setText(impl->getOR());
  ui->textBoxOV->setText(impl->getOV());
  ui->textBoxPC->setText(impl->getPC());
  ui->textBoxRA->setText(impl->getRA());
  ui->textBoxRAR->setText(impl->getRAR());
  ui->textBoxRB->setText(impl->getRB());
  ui->textBoxRDR->setText(impl->getRDR());
  ui->textBoxS->setText(impl->getS());
  ui->textBoxSP->setText(impl->getSP());
  ui->textBoxTA->setText(impl->getTA());
  ui->textBoxZ->setText(impl->getZ());

  ui->tableRegisters->clear();
  ui->tableRegisters->setColumnCount(10);
  ui->tableRegisters->setRowCount(2);

  ui->tableRegisters->horizontalHeader()->setVisible(false);
  ui->tableRegisters->verticalHeader()->setVisible(false);

  for(int k = 0; k < 10; k ++) {
    if(k % 2 == 0) {
      ui->tableRegisters->setColumnWidth(k, 30);
    } else {
      ui->tableRegisters->setColumnWidth(k, 60);
    }
  }

  int colmn = 0;
  int rNum = 0;
  for(int k = 0; k < 10; k ++) {
      ui->tableRegisters->setRowHeight(0, 30);
      ui->tableRegisters->setRowHeight(1, 30);
      if(k % 2 == 0) {
        ui->tableRegisters->setItem(0, k, new QTableWidgetItem("R" + QString::number(rNum)));
        ui->tableRegisters->setItem(1, k, new QTableWidgetItem("R" + QString::number(rNum + 1)));
      } else {
        ui->tableRegisters->setItem(0, k, new QTableWidgetItem(impl->getRegisterValue(rNum)));
        ui->tableRegisters->setItem(1, k, new QTableWidgetItem(impl->getRegisterValue(rNum + 1)));
        rNum += 2;
      }
    colmn += 2;
  }
}

void CpuWidget::on_textBoxIR_editingFinished()
{
  QString arg = ui->textBoxIR->text();
  while (arg.size() < 6) {
    arg.push_front("0");
  }
  impl->setIR(arg);
  updateGUI();
}
