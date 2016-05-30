#ifndef MEMMORYWIDGET_H
#define MEMMORYWIDGET_H

#include <QWidget>
#include "memory.h"

namespace Ui {
class MemmoryWidget;
}

class MemmoryWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MemmoryWidget(Memory *memory, QWidget *parent = 0);
  ~MemmoryWidget();

  void updateGUI();
private:
  Memory *memory;
  Ui::MemmoryWidget *ui;
};

#endif // MEMMORYWIDGET_H
