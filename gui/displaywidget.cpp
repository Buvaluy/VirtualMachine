#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DisplayWidget)
{
  ui->setupUi(this);
}

DisplayWidget::~DisplayWidget()
{
  delete ui;
}
