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


    QDateTime startDay3 = QDateTime(QDate(2019,12,8),QTime(10,10));
    QDateTime deadline3 = QDateTime(QDate(2020,1,1),QTime(10,10));

    Board board;
    QString boardTitle = "TEst";
    board.title = boardTitle;
    BoardColumn* column = new BoardColumn("Column1");

    card = new Card(title,description,creationDate,startDay,deadline);
    card2 = new Card(title,description,creationDate,startDay2,deadline2);
    card3 = new Card(title,description,creationDate,startDay3,deadline3);
    card3->status = Card::Status::Finished;

    column->AddCard(card);
    column->AddCard(card2);
    column->AddCard(card3);

    board.AddColumn(column);

    appData.boards.AddBoard(board);
}

calendar::~calendar()
{

}


void calendar::getDayCards()
{

    Calendar calendar;
    calendar.SetAppData(&appData);
    QList<Card*> cards = calendar.GetCardsForDay(QDate(2020,01,9));

    QCOMPARE(cards.size(), 2);

    if(cards.size() == 2)
    {
        Card* cardSame = cards.at(0);

        QVERIFY(card->IsEqual(cardSame));
    }


    QList<Card*> cards2 = calendar.GetCardsForDay(QDate(2020,01,11));
    if(cards.size() == 1)
    {
        Card* cardSame = cards.at(0);

        QVERIFY(card2->IsEqual(cardSame));
    }
}

void calendar::getWeekCards()
{

    Calendar calendar;
    calendar.SetAppData(&appData);
    QList<Card*> cards = calendar.GetCardsForWeek(QDate(2020,01,9));

    QCOMPARE(cards.size(), 2);

    if(cards.size() == 2)
    {
        Card* cardSame = cards.at(0);

        QVERIFY(card->IsEqual(cardSame));
    }


    QList<Card*> cards2 = calendar.GetCardsForWeek(QDate(2020,01,11));
    if(cards2.size() == 1)
    {
        Card* cardSame = cards.at(0);

        QVERIFY(card2->IsEqual(cardSame));
    }
}


void calendar::getCardsForDeadline()
{
    Calendar calendar;
    calendar.SetAppData(&appData);

    QList<Card*> cards = calendar.GetCardsForDeadline(QDateTime(QDate(2020,1,9),QTime(10,10)),10);

    QCOMPARE(cards.size(), 1);
    QVERIFY(card->IsEqual(cards[0]));

}

QTEST_APPLESS_MAIN(calendar)

