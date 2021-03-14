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

	if(selectedDate() == date)
	{
		painter->save();

		painter->fillRect(rect,QBrush(QColor(0x44,0x44,0x44)));//TODO:
		painter->restore();
	}

	if (counts > 0)
	{
		painter->save();
		const int size = 10;
		const int paddingTop = 2;
		const int paddingRight = 4;
		painter->setBrush(QBrush(QColor(0x42,0xA5,0xF5)));//TODO:
		painter->setPen(QPen(QColor(0x42,0xA5,0xF5)));//TODO:
		QRect infoRect(rect.x()+rect.width()-size-paddingRight,rect.y()+paddingTop,size,size);

		QFont font = painter->font();
		font.setFamily("Verdana");//TODO:
		font.setPixelSize(size);//TODO:
		painter->setFont(font);

		painter->drawText(infoRect, Qt::TextSingleLine | Qt::AlignCenter, QString::number(counts));
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
	else if(QDate::currentDate() == date)
	{
		painter->setPen(QPen(QColor(0xFF,0xCC,0x80)));//TODO:
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
