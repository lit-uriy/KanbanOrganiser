#ifndef CELLREMINDER_H
#define CELLREMINDER_H

#include <QWidget>
#include "datastructures/card/card.h"
#include "datastructures/reminders/remindercard.h"

namespace Ui {
class CellReminder;
}

class CellReminder : public QWidget
{
		Q_OBJECT

	public:
		explicit CellReminder(QWidget *parent = nullptr);
		explicit CellReminder(Card* card, int id,QDate date,  QWidget *parent = nullptr);
		~CellReminder();

		void UpdateCard(Card* card);
		unsigned long long GetId();

	private:
		Ui::CellReminder *ui;

		QDate date;
		unsigned long long id = -1;

		void setWidgetData(Card* card);

		void setStatusIconAndLabel(QDateTime datetime);
		void setTimeleft(QDateTime datetime);
		void setTypeIcon(bool isReminder);
        void setButtons(bool isReminder);

		void setPriorityIcon(Card::Priority priority);
};

#endif // CELLREMINDER_H
