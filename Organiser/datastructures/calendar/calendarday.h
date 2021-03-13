#ifndef CALENDARDAY_H
#define CALENDARDAY_H

#include <QDate>

class CalendarDay
{
	public:
		CalendarDay(QDate date,int eventCount)
		{
			this->date = date;
			this->eventCount = eventCount;
		}

		QDate date;
		int eventCount = 0;
};


#endif // CALENDARDAY_H
