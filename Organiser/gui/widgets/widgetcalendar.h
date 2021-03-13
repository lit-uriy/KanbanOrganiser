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

		void SetWeeklyCards(QDate date);
	private:
		Ui::WidgetCalendar *ui;
		constexpr static QSize size = QSize(600,600);

		QDate currentDate;

		Calendar calendar;
		AppData appData;

		void setHeaderLayoutWeekly(QDate date);

		void addCellWeekly(class QGridLayout* gridLayout, Card card, QDate startDate, int row);

		void setGridColumnWidths(QGridLayout* gridLayout);

	private slots:
		void onPreviousClicked();
		void onNextClicked();
		void on_calendarWidget_currentPageChanged(int year, int month);
};

#endif // WIDGETCALENDAR_H
