#include <QtTest>

// add necessary includes here


class ServerInterpreterTest : public QObject
{
		Q_OBJECT

	public:
		ServerInterpreterTest();
		~ServerInterpreterTest();

	private slots:
		void test_login_success();
		void test_login_fail();

};

ServerInterpreterTest::ServerInterpreterTest()
{

}

ServerInterpreterTest::~ServerInterpreterTest()
{

}


//QTEST_APPLESS_MAIN(ServerInterpreterTest)

//#include "tst_serverinterpreter.moc"
