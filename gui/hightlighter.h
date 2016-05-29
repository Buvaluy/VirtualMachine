#ifndef HIGHTLIGHTER_H
#define HIGHTLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QList>
#include <QStringList>

class QTextDocument;

class RuleGenerator {
  QStringList rules;
  bool isCreate = false;
public:
  QStringList getRules() {
    if(!isCreate) {
      rules << "\\bNOP\\b" << "\\bIN\\b" << "\\bOUT\\b"
            << "\\bIRET\\b" << "\\bWRRB\\b" << "\\bWRSP\\b"
            << "\\bPUSH\\b" << "\\bPOP\\b" << "\\bRET\\b"
            << "\\bHTL\\b" << "\\bJMP\\b" << "\\bJZ\\b"
            << "\\bJNZ\\b" << "\\bJS\\b" << "\\bJNS\\b"
            << "\\bJO\\b" << "\\bJNO\\b" << "\\bJRNZ\\b"
            << "\\bINT\\b" << "\\bCALL\\b" << "\\bRD\\b"
            << "\\bWR\\b" << "\\bADD\\b" << "\\bSUB\\b"
            << "\\bMUL\\b" << "\\bDIV\\b" << "\\bEI\\b"
            << "\\bDI\\b" << "\\bMOV\\b" << "\\bRD\\b"
            << "\\bWR\\b" << "\\bIN\\b" << "\\bOUT\\b"
            << "\\bRDI\\b" << "\\bADI\\b" << "\\bSBI\\b"
            << "\\bMULI\\b" << "\\bDIVI\\b";
    }

    return rules;
  }
};

class HightLighter : public QSyntaxHighlighter
{
  Q_OBJECT

public:
  HightLighter(QTextDocument *parent  = 0);

protected:

  void highlightBlock(const QString &text) override;

private:
  RuleGenerator generator;

  struct HightLighterRule {
    QRegExp pattern;
    QTextCharFormat format;
  };

  QList<HightLighterRule> rules;

  QTextCharFormat keyWordFormat;
  QTextCharFormat labelFormat;

};



#endif // HIGHTLIGHTER_H
