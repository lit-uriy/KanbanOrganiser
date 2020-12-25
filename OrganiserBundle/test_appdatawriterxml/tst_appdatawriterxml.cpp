#include <QtTest>

#include "datastructures/appData/appdata.h"
#include "datastructures/appData/appdatawriterxml.h"
#include "exceptions/generalexception.h"
#include <QDomDocument>

class test_appdatawriterxml : public QObject
{
		Q_OBJECT

	public:
		test_appdatawriterxml();
		~test_appdatawriterxml();

	private slots:
		void writeAppDataToXml();

};

test_appdatawriterxml::test_appdatawriterxml()
{

}

test_appdatawriterxml::~test_appdatawriterxml()
{

}

void test_appdatawriterxml::writeAppDataToXml()
{
	AppData appData;
	AppDataWriterXml writer;
	QDomDocument document;
	QDomElement elementAppData = writer.Save(appData,document);

	appData = writer.Load(elementAppData);

	QVERIFY(appData.IsValid());
}

QTEST_APPLESS_MAIN(test_appdatawriterxml)

#include "tst_appdatawriterxml.moc"
