#include "cpuwidget.h"
#include "ui_cpuwidget.h"

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
  ui->tableRegisters->setColumnCount(4);
  ui->tableRegisters->setRowCount(5);

  ui->tableRegisters->horizontalHeader()->setVisible(false);
  ui->tableRegisters->verticalHeader()->setVisible(false);

  ui->tableRegisters->setColumnWidth(0, 30);
  ui->tableRegisters->setColumnWidth(1, 80);
  ui->tableRegisters->setColumnWidth(2, 30);
  ui->tableRegisters->setColumnWidth(3, 80);

  int colmn = 0;
  int rNum = 0;
  for(int k = 0; k < 2; k ++) {
    for(int i = 0; i < 5; i ++) {
      ui->tableRegisters->setRowHeight(i, 29);
      ui->tableRegisters->setItem(i, colmn, new QTableWidgetItem("R" + QString::number(rNum)));
      ui->tableRegisters->setItem(i, colmn + 1, new QTableWidgetItem(impl->getRegisterValue(rNum)));
      rNum ++;
    }
    colmn += 2;
  }
}
