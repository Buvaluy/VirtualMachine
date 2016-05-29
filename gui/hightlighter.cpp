#include "hightlighter.h"

HightLighter::HightLighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{
  keyWordFormat.setForeground(Qt::darkMagenta);
  keyWordFormat.setFontWeight(QFont::Bold);

  QStringList pattern = generator.getRules();

  HightLighterRule rule;
  foreach (const QString &var, pattern) {
    rule.pattern = QRegExp(var);
    rule.format = keyWordFormat;
    rules.append(rule);
  }
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
