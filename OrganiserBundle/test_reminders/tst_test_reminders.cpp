#include <QtTest>

// add necessary includes here
#include "datastructures/reminders/remindercard.h"
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
	ReminderCard* card = new ReminderCard("Title", "Desc", QDateTime());
	reminders.AddCard(card);

	ReminderCard* card2 = new ReminderCard("Title2", "Desc2", QDateTime());
	reminders.AddCard(card);

	ReminderCard* card1Clone = reminders.GetCardAt(0);
	ReminderCard* card2CLone = reminders.GetCardAt(1);

	QVERIFY(card->IsEqual(card1Clone));
	QVERIFY(card->IsEqual(card2CLone));
}

void test_reminders::addCardToNotesAtPosition()
{
	Reminders reminders;
	ReminderCard* cardFirst= new ReminderCard("Title", "Desc", QDateTime());
	ReminderCard* cardSecond= new ReminderCard("Title2", "Desc2", QDateTime());
	ReminderCard* cardFirstAgain= new ReminderCard("Title3", "Desc3", QDateTime());

	reminders.AddCard(cardFirst);
	reminders.AddCard(cardSecond);

	reminders.AddCardAt(0,cardFirstAgain);


	ReminderCard* cardFirstAgainClone = reminders.GetCardAt(0);
	ReminderCard* cardFirstClone = reminders.GetCardAt(1);

	QVERIFY(cardFirstAgain->IsEqual(cardFirstAgainClone));
	QVERIFY(cardFirst->IsEqual(cardFirstClone));
}

void test_reminders::getCardOutOfRangeException()
{
	Reminders notes;

	ReminderCard* card = new ReminderCard("Title", "Desc", QDateTime());
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


	ReminderCard* card = new ReminderCard("Title", "Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	reminders.AddCard(card);

	ReminderCard* card2 = new ReminderCard("Title2", "Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	reminders.AddCard(card2);

	reminders.DeleteCard(card->id);

	ReminderCard* card2FromNotes = reminders.GetCards().at(0);

	QVERIFY(reminders.GetCards().size() == 1);

	QVERIFY(!card->IsEqual(card2FromNotes));
	QVERIFY(card2->IsEqual(card2FromNotes));

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

	ReminderCard* card = new ReminderCard("Title","Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	reminders.AddCard(card);

	ReminderCard* card2 = new ReminderCard("Title2","Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	reminders.ReplaceCard(card->id,card2);

	ReminderCard* cardFromNotes = reminders.GetCards().at(0);

	QVERIFY(!card->IsEqual(cardFromNotes));
	QVERIFY(card2->IsEqual(cardFromNotes));

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

	ReminderCard* card = new ReminderCard("Title","Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	reminders.AddCard(card);

	ReminderCard*  card2 = new ReminderCard("Title2","Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	reminders.AddCard(card2);

	ReminderCard*  card3 = new ReminderCard("Title3","Desc3", QDateTime(QDate(2019,2,4),QTime(4,8)));

	int index2 = reminders.Find(card2);
	ReminderCard*  card2Copy = reminders.GetCardAt(index2);

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
