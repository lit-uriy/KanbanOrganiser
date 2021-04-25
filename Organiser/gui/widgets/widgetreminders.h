#ifndef WIDGETREMINDERS_H
#define WIDGETREMINDERS_H

#include <QWidget>

#include "datastructures/appData/appdata.h"
#include "datastructures/calendar/calendar.h"
#include "datastructures/reminders/reminders.h"
#include "widgettab.h"

namespace Ui {
class WidgetReminders;
}

class WidgetReminders : public WidgetTab
{
		Q_OBJECT

	public:
		explicit WidgetReminders(QWidget *parent = nullptr);
		~WidgetReminders();

        void SetAppData(AppData* appData);
		void UpdateData(QDate date);

        Reminders* GetReminders();
	private slots:
		void on_pushButton_clicked();

		void on_twdReminders_customContextMenuRequested(const QPoint &pos);

		void on_actionEditReminder_triggered();

		void on_actionDeleteReminder_triggered();

	private:
		Ui::WidgetReminders *ui;
		constexpr static QSize size = QSize(300,600);

		QDate date;
		Calendar calendar;
        Reminders* reminders = nullptr;
        AppData* appData = nullptr;

		void addCardToListView(Card* card, int id,QDate date);

		void addReminder();

		unsigned long long getSelectedCardID();
		class CellReminder* getSelectedCell();
		int getSelectedCellIndex();
		void replaceSelectedCard(Card* card);
		void deleteCard(unsigned long long id);

	signals:
		void reminderAdded();
};

#endif // WIDGETREMINDERS_H
