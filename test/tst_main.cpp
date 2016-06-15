#ifndef TST_MAIN_CPP
#define TST_MAIN_CPP
#include <QtTest/QtTest>
#include "commandsimpl.h"
#include <QString>

class TestAbstractCommand: public QObject {
	Q_OBJECT
	private slots:
		void push3times0();
		void push3times0_data();
};

void TestAbstractCommand::push3times0_data() {

	QTest::addColumn<QString>("string");
	QTest::addColumn<QString>("result");

	QTest::newRow("Empty string") << "" << "000";
	QTest::newRow("One number") << "1" << "001";
	QTest::newRow("Two numbers") << "12" << "012";
}

void TestAbstractCommand::push3times0() {
	CPU cpu;
	Memory mem;
	CommandImplIn cii(&cpu, &mem);

	QFETCH(QString, string);
	QFETCH(QString, result);

	cii.push3Times0(string);

	QCOMPARE(string, result);
}


//QTEST_MAIN(TestAbstractCommand)
#include "tst_main.moc"
#endif // TST_MAIN_CPP
