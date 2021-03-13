#ifndef REMINDERCALENDAR_H
#define REMINDERCALENDAR_H

#include <QCalendarWidget>
#include "datastructures/calendar/calendarday.h"

class ReminderCalendar : public QCalendarWidget
{
	Q_OBJECT

	public:
		ReminderCalendar(QWidget* parent=nullptr);

		void SetCalendarDays(QList<CalendarDay> calendarDays);
	protected:
		void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;


	private:
		QList<CalendarDay> calendarDays;

		int getReminderCount(QDate date) const;
};

#endif // REMINDERCALENDAR_H
