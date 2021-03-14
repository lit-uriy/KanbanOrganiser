#ifndef WIDGETCALENDAR_H
#define WIDGETCALENDAR_H

#include <QWidget>

#include "datastructures/appData/appdata.h"
#include "datastructures/calendar/calendar.h"
#include "widgettab.h"


namespace Ui {
class WidgetCalendar;
}

class WidgetCalendar : public WidgetTab
{
		Q_OBJECT

	public:
		explicit WidgetCalendar(QWidget *parent = nullptr);
		~WidgetCalendar();
		void SetAppData(AppData appData);

		Reminders GetReminders();
	private:
		Ui::WidgetCalendar *ui;
		constexpr static QSize size = QSize(300,600);

		Calendar calendar;
		AppData appData;

		void updateReminders();

	private slots:
		void OnReminderAdded();
		void on_calendarWidget_currentPageChanged(int year, int month);
		void on_calendarWidget_selectionChanged();

	signals:
		void reminderAdded();
};

#endif // WIDGETCALENDAR_H
