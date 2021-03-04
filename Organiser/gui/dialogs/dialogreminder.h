#ifndef DIALOGREMINDER_H
#define DIALOGREMINDER_H

#include <QDialog>
#include "datastructures/reminders/remindercard.h"

namespace Ui {
class DialogReminder;
}

class DialogReminder : public QDialog
{
		Q_OBJECT

	public:
		explicit DialogReminder(QWidget *parent = nullptr);
		explicit DialogReminder(ReminderCard card, QWidget *parent = nullptr);
		~DialogReminder();

		ReminderCard GetReminderCard();

	private:
		Ui::DialogReminder *ui;
		ReminderCard card;

		void changeAcceptButtonToApply();
		void setWidgetData(ReminderCard card);

	private slots:
		void on_btnAccept_clicked();

		void on_btnCancel_clicked();
};

#endif // DIALOGREMINDER_H
