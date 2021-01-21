#include "calendar.h"

Calendar::Calendar()
{

}

QList<Card> Calendar::GetCardsForDay(QDate date, AppData appData)
{
	QList<Card> cards;

	for(int i=0; i < appData.boards.size();i++)
	{
		Board board = appData.boards.at(i);

		for(int j=0; j < board.GetColumnCount();j++)
		{
			BoardColumn column = board.GetColumnAt(j);

			for(int k=0; k < column.GetCardsCount();k++)
			{
				Card card = column.GetCardAt(k);

				if(card.startDate.date() <= date && date <= card.deadline.date())
				{
					cards.append(card);
				}
			}
		}
	}

	return cards;
}


QList<Card> Calendar::GetCardsForWeek(QDate date, AppData appData)
{
	QList<Card> cards;

	int dayNumber = date.dayOfWeek()-1;

	QDate startDay = date.addDays(-dayNumber);
	QDate endDay = startDay.addDays(6);

	for(int i=0; i < appData.boards.size();i++)
	{
		Board board = appData.boards.at(i);

		for(int j=0; j < board.GetColumnCount();j++)
		{
			BoardColumn column = board.GetColumnAt(j);

			for(int k=0; k < column.GetCardsCount();k++)
			{
				Card card = column.GetCardAt(k);

				if(card.startDate.date() <= startDay && startDay <= card.deadline.date())
				{
					cards.append(card);
				}
				else if(card.startDate.date() <= endDay && endDay <= card.deadline.date())
				{
					cards.append(card);
				}
				else if(startDay <= card.startDate.date() && card.startDate.date() <= endDay)
				{
					cards.append(card);
				}
			}
		}
	}

	return cards;
}
