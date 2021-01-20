#include "tst_calendar.h"

#include "datastructures/calendar/calendar.h"
#include "datastructures/board/board.h"
#include "datastructures/appData/appdata.h"

calendar::calendar()
{

}

calendar::~calendar()
{

}


void calendar::getDayCards()
{
	QString title = "titleText";
	QString description  = "descriptionText";
	QDateTime creationDate = QDateTime(QDate(2020,1,1),QTime(10,10));
	QDateTime startDay = QDateTime(QDate(2020,1,1),QTime(10,10));
	QDateTime deadline = QDateTime(QDate(2020,1,10),QTime(10,10));

	Board board;
	QString boardTitle = "TEst";
	board.title = boardTitle;
	BoardColumn column("Column1");

	Card card(title,description,creationDate,startDay,deadline);

	column.AddCard(card);

	board.AddColumn(column);

	AppData appData;
	appData.boards.append(board);


	Calendar calendar;
	QList<Card> cards = calendar.GetCardsForDay(QDate(2020,01,10),appData);

	QCOMPARE(cards.size(), 1);

	if(cards.size() == 1)
	{
		Card cardSame =cards.at(0);

		QVERIFY(card == cardSame);
	}
}

void calendar::getWeekCards()
{

}

QTEST_APPLESS_MAIN(calendar)

