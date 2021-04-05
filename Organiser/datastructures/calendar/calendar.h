#ifndef CALENDAR_H
#define CALENDAR_H

#include <QList>
#include "datastructures/card/card.h"
#include "datastructures/appData/appdata.h"
#include "calendarday.h"
#include "postponedcard.h"

class Calendar
{
	public:
		Calendar();

		QList<Card*> GetCardsForDay(QDate date, AppData appData);

		QList<Card*> GetCardsForWeek(QDate date, AppData appData);

		QList<CalendarDay> GetCalendarDaysForMonth(QDate date,AppData appData);

		QList<Card*> GetCardsForDeadline(QDateTime datetime, AppData appData, int addedMinutes=60);

	private:
		bool shouldShowCard(Card* card,QDateTime datetime,int addedMinutes);
};

#endif // CALENDAR_H
