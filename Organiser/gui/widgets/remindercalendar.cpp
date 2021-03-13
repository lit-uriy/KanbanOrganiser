#include "remindercalendar.h"

#include <QPainter>

ReminderCalendar::ReminderCalendar(QWidget* parent) : QCalendarWidget(parent)

{

}

void ReminderCalendar::SetCalendarDays(QList<CalendarDay> calendarDays)
{
	this->calendarDays = calendarDays;
}

void ReminderCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
	//QCalendarWidget::paintCell(painter, rect, date);


	const int counts = getReminderCount(date);

	painter->setRenderHint(QPainter::Antialiasing);
	painter->save();

	if (counts > 0)
	{
		const int size = 8;
		const int padding = 6;
		painter->setBrush(QBrush(QColor(0x42,0xA5,0xF5)));//TODO:
		painter->setPen(Qt::NoPen);
		QRect infoRect(rect.x()+rect.width()-size-padding,rect.y()+padding,size,size);

		painter->drawEllipse(infoRect);

		painter->restore();
	}

	painter->save();
	if(selectedDate() == date)
	{
		painter->setPen(QPen(QColor(0x42,0xA5,0xF5)));//TODO:
	}
	else if(date.month() != monthShown())
	{
		painter->setPen(QPen(QColor(0x88,0x88,0x88)));//TODO:
	}
	painter->drawText(rect, Qt::TextSingleLine | Qt::AlignCenter, QString::number(date.day()));


	painter->restore();
}

int ReminderCalendar::getReminderCount(QDate date) const
{
	for(int i=0; i < calendarDays.size();i++)
	{
		if(calendarDays.at(i).date == date)
		{
			return calendarDays.at(i).eventCount;
		}
	}

	return 0;
}
