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

				if(card.startDate.date() == date || card.deadline.date() == date)
				{
					cards.append(card);
				}
			}
		}
	}

	return cards;
}
