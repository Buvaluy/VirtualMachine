#include "hightlighter.h"

HightLighter::HightLighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{
  keyWordFormat.setForeground(Qt::darkBlue);
  keyWordFormat.setFontWeight(QFont::Bold);

  labelFormat.setForeground(Qt::darkMagenta);
  labelFormat.setFontWeight(QFont::Bold);

  QStringList pattern = generator.getRules();

  HightLighterRule rule;
  foreach (const QString &var, pattern) {
    rule.pattern = QRegExp(var);
    rule.format = keyWordFormat;
    rules.append(rule);
  }

  rule.pattern = QRegExp("\\b[A-Za-z0-9_]+:");
  rule.format = labelFormat;
  rules.append(rule);
}

void HightLighter::highlightBlock(const QString &text)
{
  foreach (const HightLighterRule &rule, rules) {
      QRegExp expression(rule.pattern);
      int index = expression.indexIn(text);
      while (index >= 0) {
          int length = expression.matchedLength();
          setFormat(index, length, rule.format);
          index = expression.indexIn(text, index + length);
      }
  }
}
