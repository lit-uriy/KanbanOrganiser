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

        void SetAppData(AppData* appData);//TODO:const

        QList<Card*> GetCardsForDay(QDate date);

        QList<Card*> GetCardsForWeek(QDate date);

        QList<CalendarDay> GetCalendarDaysForMonth(QDate date);

        QList<Card*> GetCardsForDeadline(QDateTime datetime, int addedMinutes=60);

	private:
        AppData* appData = nullptr;
		bool shouldShowCard(Card* card,QDateTime datetime,int addedMinutes);
};

#endif // CALENDAR_H
