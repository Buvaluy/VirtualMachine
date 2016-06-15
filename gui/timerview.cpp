#include "timerview.h"
#include "ui_timerview.h"

TimerView::TimerView(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TimerView)
{
  ui->setupUi(this);
}

TimerView::~TimerView()
{
  delete ui;
}
