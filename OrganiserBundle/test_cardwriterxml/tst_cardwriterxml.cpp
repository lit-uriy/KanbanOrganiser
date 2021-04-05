#include "test_cardwriterxml.h"

#include "datastructures/card/card.h"
#include "datastructures/card/cardwriterxml.h"

test_cardwriterxml::test_cardwriterxml()
{

}

test_cardwriterxml::~test_cardwriterxml()
{

}

void test_cardwriterxml::writeCardToXml()
{
	QString title = "titleText";
	QString description  = "descriptionText";
	QDateTime creationDate = QDateTime(QDate(2020,1,1),QTime(10,10));

	Card* card = new Card(title,description,creationDate);

	CardWriterXml writer;
	QDomDocument document;
	QDomElement elementCard = writer.Save(card,document);

	Card* cardLoaded = writer.Load(elementCard);

	QVERIFY(card->IsEqual(cardLoaded));
}

QTEST_APPLESS_MAIN(test_cardwriterxml)

