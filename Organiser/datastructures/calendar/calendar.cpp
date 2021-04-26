#include "calendar.h"

Calendar::Calendar()
{

}

void Calendar::SetAppData(AppData* appData)
{
    this->appData = appData;
}

QList<Card*> Calendar::GetCardsForDay(QDate date)
{
	QList<Card*> cards;

    for(int i=0; i < appData->boards.GetSize();i++)
	{
        Board* board = appData->boards.GetBoard(i);

        for(int j=0; j < board->GetColumnCount();j++)
		{
            BoardColumn* column = board->GetColumnAt(j);

            for(int k=0; k < column->GetCardsCount();k++)
			{
                Card* card = column->GetCardAt(k);

				if(card->startDate.date() <= date && date <= card->deadline.date())
				{
					cards.append(card);
				}
			}
		}
	}

    for(int i=0; i < appData->reminders.GetCardsCount();i++)
	{
        ReminderCard* card = appData->reminders.GetCardAt(i);
		if(card->deadline.date() == date)
		{
			cards.append(card);
		}
	}

	return cards;
}


QList<Card*> Calendar::GetCardsForWeek(QDate date)
{
	QList<Card*> cards;

	int dayNumber = date.dayOfWeek()-1;

	QDate weekStartDay = date.addDays(-dayNumber);
	QDate weekEndDay = weekStartDay.addDays(6);

    for(int i=0; i < appData->boards.GetSize();i++)
	{
        Board* board = appData->boards.GetBoard(i);

        for(int j=0; j < board->GetColumnCount();j++)
		{
            BoardColumn* column = board->GetColumnAt(j);

            for(int k=0; k < column->GetCardsCount();k++)
			{
                Card* card = column->GetCardAt(k);

				QDate cardStartDay = card->startDate.date();
				QDate cardEndDay = card->deadline.date();

				if(weekStartDay <= cardStartDay && cardStartDay <= weekEndDay)
				{
					cards.append(card);
				}
				else if(weekStartDay <= cardEndDay && cardEndDay <= weekEndDay)
				{
					cards.append(card);
				}
				else if(cardEndDay <= weekStartDay && weekEndDay <= cardEndDay)
				{
					cards.append(card);
				}
			}
		}
	}

    for(int i=0; i < appData->reminders.GetCardsCount();i++)
	{
        ReminderCard* card = appData->reminders.GetCardAt(i);
		QDate cardStartDay = card->startDate.date();
		QDate cardEndDay = card->deadline.date();

		if(weekStartDay <= cardStartDay && cardStartDay <= weekEndDay)
		{
			cards.append(card);
		}
		else if(weekStartDay <= cardEndDay && cardEndDay <= weekEndDay)
		{
			cards.append(card);
		}
		else if(cardEndDay <= weekStartDay && weekEndDay <= cardEndDay)
		{
			cards.append(card);
		}
	}
	return cards;
}

QList<CalendarDay> Calendar::GetCalendarDaysForMonth(QDate date)
{
	QList<CalendarDay> list;

	const int daysInMonth = date.daysInMonth();

	for(int i=1; i < daysInMonth+1;i++)
	{
		QDate day(date.year(),date.month(),i);


        int count = GetCardsForDay(day).size();

		if(count > 0)
		{
			list.append(CalendarDay(day,count));
		}
	}

	return list;
}

QList<Card*> Calendar::GetCardsForDeadline(QDateTime datetime, int addedMinutes)
{
	QList<Card*> cards;

	//TODO:Add Iterator thourgh all cards in all subobjects
    for(int i=0; i < appData->boards.GetSize();i++)
	{
        Board* board = appData->boards.GetBoard(i);

        for(int j=0; j < board->GetColumnCount();j++)
		{
            BoardColumn* column = board->GetColumnAt(j);

            for(int k=0; k < column->GetCardsCount();k++)
			{
                Card* card = column->GetCardAt(k);

				if(shouldShowCard(card,datetime,addedMinutes))
				{
					cards.push_back(card);
				}
			}
		}
	}

    for(int i=0; i < appData->reminders.GetCardsCount();i++)
	{
        ReminderCard* card = appData->reminders.GetCardAt(i);

		if(shouldShowCard(card,datetime,addedMinutes))
		{
			cards.push_back(card);
		}
	}

	return cards;
}


bool Calendar::shouldShowCard(Card* card,QDateTime datetime,int addedMinutes)
{
    if(!card->deadline.isValid())
    {
        return false;
    }

	if(card->postponedDeadline.isValid())
	{
        if(card->postponedDeadline <= datetime && card->status == Card::Status::Started && !card->markedAsShown)
		{
			return true;
		}
	}
	else
	{

        if(card->deadline <= datetime.addSecs(60*addedMinutes) && card->status == Card::Status::Started && !card->markedAsShown)
		{
			return true;
		}
	}

	return false;
}
