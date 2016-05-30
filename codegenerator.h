#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <QMap>
#include <QString>

class CodeGenerator
{
protected:
    QMap <QString, QString> mCode;

public:
    CodeGenerator();

    QString getCode(QString code);
};

#endif // CODEGENERATOR_H
