#ifndef WIDGETCALENDAR_H
#define WIDGETCALENDAR_H

#include <QWidget>

#include "datastructures/appData/appdata.h"
#include "datastructures/calendar/calendar.h"

namespace Ui {
class WidgetCalendar;
}

class WidgetCalendar : public QWidget
{
		Q_OBJECT

	public:
		explicit WidgetCalendar(QWidget *parent = nullptr);
		~WidgetCalendar();
		void SetAppData(AppData appData);

		void SetWeeklyCards(QDate date);
	private:
		Ui::WidgetCalendar *ui;

		QDate currentDate;

		Calendar calendar;
		AppData appData;

		void setHeaderLayoutWeekly(QDate date);

		void addCellWeekly(class QGridLayout* gridLayout, Card card, QDate startDate, int row);

		void setGridColumnWidths(QGridLayout* gridLayout);

	private slots:
		void onPreviousClicked();
		void onNextClicked();
};

#endif // WIDGETCALENDAR_H
