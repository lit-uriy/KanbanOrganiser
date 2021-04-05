

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

	QDateTime startDate = QDateTime(QDate(2020,1,1),QTime(10,10));
	QDateTime deadline = QDateTime(QDate(2021,2,10),QTime(11,9));

	Card* card = new Card(title,description,creationDate,startDate,deadline);

	QCOMPARE(title, card->title);
	QCOMPARE(description, card->description);
	QCOMPARE(creationDate, card->creationDate);
	QCOMPARE(startDate, card->startDate);
	QCOMPARE(deadline, card->deadline);
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

	QVERIFY(card.IsEqual(&cardSame));
	QVERIFY(!card.IsEqual(&cardDiffTitle));
	QVERIFY(!card.IsEqual(&carDiffDesc));
	QVERIFY(!card.IsEqual(&carDiffCreateDate));
}

void TestCard::test_EncodeDecode()
{
	QString title = "titleText";
	QString description  = "descriptionText";
	QDateTime creationDate = QDateTime(QDate(2020,1,1),QTime(10,10));

	QDateTime startDate = QDateTime(QDate(2020,1,10),QTime(9,9));
	QDateTime deadline = QDateTime(QDate(2020,2,2),QTime(11,11));

	Card card(title,description,creationDate,startDate,deadline);
	Card cardDecoded(card.Encode());


	QVERIFY(card.IsEqual(&cardDecoded));
}

QTEST_APPLESS_MAIN(TestCard)

