

// add necessary includes here
#include "tst_card.h"
#include "datastructures/card/card.h"


TestCard::TestCard()
{

}

TestCard::~TestCard()
{

}

void TestCard::test_cardCreation()
{
	QString title = "titleText";
	QString description  = "descriptionText";
	QDateTime creationDate = QDateTime::currentDateTime();

	Card* card = new Card(title,description,creationDate);

	QCOMPARE(title, card->title);
	QCOMPARE(description, card->description);
	QCOMPARE(creationDate, card->creationDate);
}

void TestCard::test_compare()
{
	QString title = "titleText";
	QString title2 = "otherTitle";
	QString description  = "descriptionText";
	QString description2  = "OtherDesc";
	QDateTime creationDate = QDateTime(QDate(2020,1,1),QTime(10,10));
	QDateTime creationDate2 = QDateTime(QDate(2019,2,4),QTime(4,8));

	Card card(title,description,creationDate);
	Card cardSame(title,description,creationDate);

	Card cardDiffTitle(title2,description,creationDate);
	Card carDiffDesc(title,description2,creationDate);
	Card carDiffCreateDate(title,description,creationDate2);

	QVERIFY(card == cardSame);
	QVERIFY(card != cardDiffTitle);
	QVERIFY(card != carDiffDesc);
	QVERIFY(card != carDiffCreateDate);
}

QTEST_APPLESS_MAIN(TestCard)

