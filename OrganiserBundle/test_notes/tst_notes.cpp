
#include "test_notes.h"
// add necessary includes here

#include "datastructures/card/card.h"
#include "datastructures/notes/notes.h"
#include "exceptions/generalexception.h"



test_notes::test_notes()
{

}

test_notes::~test_notes()
{

}

void test_notes::addCardToNotes()
{
	Notes notes;
	Card card("Title", "Desc", QDateTime());
	notes.AddCard(card);

	Card card2("Title2", "Desc2", QDateTime());
	notes.AddCard(card);

	Card card1Clone = notes.GetCardAt(0);
	Card card2CLone = notes.GetCardAt(1);

	QVERIFY(card == card1Clone);
	QVERIFY(card == card2CLone);
}

void test_notes::addCardToNotesAtPosition()
{
	Notes notes;
	Card cardFirst("Title", "Desc", QDateTime());
	Card cardSecond("Title2", "Desc2", QDateTime());
	Card cardFirstAgain("Title3", "Desc3", QDateTime());

	notes.AddCard(cardFirst);
	notes.AddCard(cardSecond);

	notes.AddCardAt(0,cardFirstAgain);


	Card cardFirstAgainClone = notes.GetCardAt(0);
	Card cardFirstClone = notes.GetCardAt(1);

	QVERIFY(cardFirstAgain == cardFirstAgainClone);
	QVERIFY(cardFirst == cardFirstClone);
}

void test_notes::getCardOutOfRangeException()
{
	Notes notes;

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

void test_notes::deleteCardFromNotes()
{
	Notes notes;


	Card card("Title", "Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	notes.AddCard(card);

	Card card2("Title2", "Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	notes.AddCard(card2);

	notes.DeleteCard(0);

	Card card2FromNotes = notes.GetCards().at(0);

	QVERIFY(notes.GetCards().size() == 1);

	QVERIFY(card != card2FromNotes);
	QVERIFY(card2 == card2FromNotes);

	try
	{
		notes.DeleteCard(-1);
		notes.DeleteCard(2);
		QFAIL("Failed to catch exception in DeleteCard");
	}
	catch (GeneralException exception)
	{

	}
}

void test_notes::editCardInNotes()
{
	Notes notes;

	Card card("Title","Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	notes.AddCard(card);

	Card card2("Title2","Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	notes.ReplaceCard(0,card2);

	Card cardFromNotes = notes.GetCards().at(0);

	QVERIFY(card != cardFromNotes);
	QVERIFY(card2 == cardFromNotes);

	try
	{
		notes.ReplaceCard(-1,card2);
		notes.ReplaceCard(2,card2);
		QFAIL("Failed to catch exception in ReplaceCard");
	}
	catch (GeneralException exception)
	{

	}
}


void test_notes::findCard()
{
	Notes notes;

	Card card("Title","Desc", QDateTime(QDate(2020,1,1),QTime(10,10)));
	notes.AddCard(card);

	Card card2("Title2","Desc2", QDateTime(QDate(2019,2,4),QTime(4,8)));
	notes.AddCard(card2);

	Card card3("Title3","Desc3", QDateTime(QDate(2019,2,4),QTime(4,8)));

	int index2 = notes.Find(card2);
	Card card2Copy = notes.GetCardAt(index2);

	int index3 = notes.Find(card3);


	QVERIFY(card2 == card2Copy);
	QVERIFY(card != card2Copy);

	try
	{
		notes.GetCardAt(index3);
		QFAIL("Failed to catch exception in GetCardAt");
	}
	catch (GeneralException exception)
	{

	}


}

QTEST_APPLESS_MAIN(test_notes)

