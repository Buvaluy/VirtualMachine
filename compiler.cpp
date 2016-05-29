#include "compiler.h"

#include <QStringList>

Compiler::Compiler()
{

}

QString Compiler::parseLabel(QString &strSource)
{
  strSource = strSource.replace("\n", " ");
  QStringList slCommandPair = strSource.split(" ");
  QMap<QString, int> mapLabel;

  for(int i = 0; i < slCommandPair.size(); i ++) {
    QString var = slCommandPair.at(i);
    if(var.indexOf(":") > 0) {
      QString lbl = var;
      int line = i / 2;
      slCommandPair.removeAt(i);
      mapLabel.insert(lbl, line);
    }
  }

  for(auto itr = mapLabel.begin(); itr != mapLabel.end(); itr ++) {
    for(int i = 0; i < slCommandPair.size(); i ++) {
      if(slCommandPair.at(i) == itr.key()) {
        slCommandPair.replace(i, QString::number(itr.value()));
      }
    }
  }

  strSource = slCommandPair.join(" ");

  return strSource;
}
