#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include <QWidget>
#include "cpu.h"

namespace Ui {
class CpuWidget;
}

class CpuWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CpuWidget(CPU *cpu, QWidget *parent = 0);
  ~CpuWidget();

private:
  Ui::CpuWidget *ui;
  CPU *impl;
public:
  void updateGUI();
private slots:
  void on_textBoxIR_editingFinished();
};

#endif // CPUWIDGET_H
