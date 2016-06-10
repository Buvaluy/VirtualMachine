#include "keyview.h"
#include "ui_keyview.h"

KeyView::KeyView(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::KeyView)
{
  ui->setupUi(this);
}

KeyView::~KeyView()
{
  delete ui;
}
