#ifndef WIDGETREMINDERS_H
#define WIDGETREMINDERS_H

#include <QWidget>

#include "datastructures/appData/appdata.h"
#include "datastructures/calendar/calendar.h"

namespace Ui {
class WidgetReminders;
}

class WidgetReminders : public QWidget
{
		Q_OBJECT

	public:
		explicit WidgetReminders(QWidget *parent = nullptr);
		~WidgetReminders();

		void SetAppData(AppData appData);
		void UpdateData(QDate date);
	private:
		Ui::WidgetReminders *ui;

		Calendar calendar;
		AppData appData;
		void addCardToListView(Card card, int id);
};

#endif // WIDGETREMINDERS_H
