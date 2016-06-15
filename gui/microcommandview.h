#ifndef MICROCOMMANDVIEW_H
#define MICROCOMMANDVIEW_H

#include <QWidget>

namespace Ui {
class MicroCommandView;
}

class MicroCommandView : public QWidget
{
  Q_OBJECT

public:
  explicit MicroCommandView(QWidget *parent = 0);
  ~MicroCommandView();

  void updateGui(QStringList microCommandList, int currentMicroCommand);
private:
  Ui::MicroCommandView *ui;

  void initializeTableHeadr(int countRow);
};

#endif // MICROCOMMANDVIEW_H
