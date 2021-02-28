#include <QtTest>

// add necessary includes here
#include "datastructures/card/card.h"
#include "datastructures/reminders/reminders.h"
#include "exceptions/generalexception.h"


class test_reminders : public QObject
{
		Q_OBJECT

	public:
		test_reminders();
		~test_reminders();

	private slots:
		void addCardToNotes();
		void addCardToNotesAtPosition();
		void getCardOutOfRangeException();
		void deleteCardFromNotes();
		void editCardInNotes();
		void findCard();


};

test_reminders::test_reminders()
{

}

test_reminders::~test_reminders()
{

}

void test_reminders::addCardToNotes()
{
	Reminders reminders;
	Card card("Title", "Desc", QDateTime());
	reminders.AddCard(card);

	Card card2("Title2", "Desc2", QDateTime());
	reminders.AddCard(card);

	Card card1Clone = reminders.GetCardAt(0);
	Card card2CLone = reminders.GetCardAt(1);

	QVERIFY(card == card1Clone);
	QVERIFY(card == card2CLone);
}

void test_reminders::addCardToNotesAtPosition()
{
	Reminders reminders;
	Card cardFirst("Title", "Desc", QDateTime());
	Card cardSecond("Title2", "Desc2", QDateTime());
	Card cardFirstAgain("Title3", "Desc3", QDateTime());

	reminders.AddCard(cardFirst);
	reminders.AddCard(cardSecond);

	reminders.AddCardAt(0,cardFirstAgain);


	Card cardFirstAgainClone = reminders.GetCardAt(0);
	Card cardFirstClone = reminders.GetCardAt(1);

	QVERIFY(cardFirstAgain == cardFirstAgainClone);
	QVERIFY(cardFirst == cardFirstClone);
}

void test_reminders::getCardOutOfRangeException()
{
	Reminders notes;

	Card card("Title", "Desc", QDateTime());
	notes.AddCard(card);

	try
	{
		notes.GetCardAt(-1);
		notes.GetCardAt(2);
		QFAIL("Failed to catch exception in GetCardAt");
	}
	catch (GeneralException exception)
	{

	}
}

void test_reminders::deleteCardFromNotes()
{
	Reminders reminders;


	Card card("Title", "Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	reminders.AddCard(card);

	Card card2("Title2", "Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	reminders.AddCard(card2);

	reminders.DeleteCard(0);

	Card card2FromNotes = reminders.GetCards().at(0);

	QVERIFY(reminders.GetCards().size() == 1);

	QVERIFY(card != card2FromNotes);
	QVERIFY(card2 == card2FromNotes);

	try
	{
		reminders.DeleteCard(-1);
		reminders.DeleteCard(2);
		QFAIL("Failed to catch exception in DeleteCard");
	}
	catch (GeneralException exception)
	{

	}
}

void test_reminders::editCardInNotes()
{
	Reminders reminders;

	Card card("Title","Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	reminders.AddCard(card);

	Card card2("Title2","Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	reminders.ReplaceCard(0,card2);

	Card cardFromNotes = reminders.GetCards().at(0);

	QVERIFY(card != cardFromNotes);
	QVERIFY(card2 == cardFromNotes);

	try
	{
		reminders.ReplaceCard(-1,card2);
		reminders.ReplaceCard(2,card2);
		QFAIL("Failed to catch exception in ReplaceCard");
	}
	catch (GeneralException exception)
	{

	}
}


void test_reminders::findCard()
{
	Reminders reminders;

	Card card("Title","Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	reminders.AddCard(card);

	Card card2("Title2","Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	reminders.AddCard(card2);

	Card card3("Title3","Desc3", QDateTime(QDate(2019,2,4),QTime(4,8)));

	int index2 = reminders.Find(card2);
	Card card2Copy = reminders.GetCardAt(index2);

	int index3 = reminders.Find(card3);


	QVERIFY(card2 == card2Copy);
	QVERIFY(card != card2Copy);

	try
	{
		reminders.GetCardAt(index3);
		QFAIL("Failed to catch exception in GetCardAt");
	}
	catch (GeneralException exception)
	{

	}


}


QTEST_APPLESS_MAIN(test_reminders)

#include "tst_test_reminders.moc"
