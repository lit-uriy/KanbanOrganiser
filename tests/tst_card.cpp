#include <QtTest>

// add necessary includes here

#include "card/card.h"

class TestCard : public QObject
{
		Q_OBJECT

	public:
		TestCard();
		~TestCard();

	private slots:
		void test_cardCreation();

};

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



QTEST_APPLESS_MAIN(TestCard)

#include "tst_card.moc"
