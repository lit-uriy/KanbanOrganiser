#include "tst_calendar.h"

#include "datastructures/calendar/calendar.h"
#include "datastructures/board/board.h"

calendar::calendar()
{
	QString title = "titleText";
	QString description  = "descriptionText";
	QDateTime creationDate = QDateTime(QDate(2020,1,1),QTime(10,10));
	QDateTime startDay = QDateTime(QDate(2020,1,7),QTime(10,10));
	QDateTime deadline = QDateTime(QDate(2020,1,9),QTime(10,10));

	QDateTime startDay2 = QDateTime(QDate(2020,1,8),QTime(10,10));
	QDateTime deadline2 = QDateTime(QDate(2020,1,20),QTime(10,10));

	Board board;
	QString boardTitle = "TEst";
	board.title = boardTitle;
	BoardColumn column("Column1");

	card = Card(title,description,creationDate,startDay,deadline);
	card2 = Card(title,description,creationDate,startDay2,deadline2);

	column.AddCard(card);
	column.AddCard(card2);

	board.AddColumn(column);

	appData.boards.append(board);
}

calendar::~calendar()
{

}


void calendar::getDayCards()
{

	Calendar calendar;
	QList<Card> cards = calendar.GetCardsForDay(QDate(2020,01,9),appData);

	QCOMPARE(cards.size(), 2);

	if(cards.size() == 2)
	{
		Card cardSame = cards.at(0);

		QVERIFY(card == cardSame);
	}


	QList<Card> cards2 = calendar.GetCardsForDay(QDate(2020,01,11),appData);
	if(cards.size() == 1)
	{
		Card cardSame = cards.at(0);

		QVERIFY(card2 == cardSame);
	}
}

void calendar::getWeekCards()
{

	Calendar calendar;
	QList<Card> cards = calendar.GetCardsForWeek(QDate(2020,01,9),appData);

	QCOMPARE(cards.size(), 2);

	if(cards.size() == 2)
	{
		Card cardSame = cards.at(0);

		QVERIFY(card == cardSame);
	}


	QList<Card> cards2 = calendar.GetCardsForWeek(QDate(2020,01,11),appData);
	if(cards.size() == 1)
	{
		Card cardSame = cards.at(0);

		QVERIFY(card2 == cardSame);
	}
}

QTEST_APPLESS_MAIN(calendar)

