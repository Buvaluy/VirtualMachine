#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <QWidget>

namespace Ui {
class TimerView;
}

class TimerView : public QWidget
{
  Q_OBJECT

public:
  explicit TimerView(QWidget *parent = 0);
  ~TimerView();

private:
  Ui::TimerView *ui;
};

#endif // TIMERVIEW_H
