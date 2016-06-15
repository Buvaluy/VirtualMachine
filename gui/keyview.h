#ifndef KEYVIEW_H
#define KEYVIEW_H

#include <QWidget>

namespace Ui {
class KeyView;
}

class KeyView : public QWidget
{
  Q_OBJECT

public:
  explicit KeyView(QWidget *parent = 0);
  ~KeyView();

private:
  Ui::KeyView *ui;
};

#endif // KEYVIEW_H
