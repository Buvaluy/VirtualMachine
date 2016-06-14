#include <QtTest/QtTest>
#include "cpu.h"
#include <QString>
#include <iostream>

class TestCpu: public QObject {
	Q_OBJECT
	private slots:
		void regToInt();
		void regToInt_data();
		void intToReg();
		void intToReg_data();
};

void TestCpu::regToInt_data() {

	QTest::addColumn<QString>("string");
	QTest::addColumn<int>("result");

	QTest::newRow("Positive") << "0001312" << 1312;
	QTest::newRow("Negative") << "1001312" << -1312;
}

void TestCpu::regToInt() {
	CPU cpu;

	QFETCH(QString, string);
	QFETCH(int, result);

	int got = cpu.convertRegToInt(string);

	QCOMPARE(result, got);
}

void TestCpu::intToReg_data() {

	QTest::addColumn<int>("value");
	QTest::addColumn<QString>("result");

	QTest::newRow("Positive") <<  1312 << "001312";
	QTest::newRow("Negative") << -1312 << "101312";
}

void TestCpu::intToReg() {
	CPU cpu;

	QFETCH(int, value);
	QFETCH(QString, result);

	QString got = cpu.convertIntToReg(value);

	QCOMPARE(got, result);
}


//QTEST_MAIN(TestCpu)
#include "tst_cpu.moc"
