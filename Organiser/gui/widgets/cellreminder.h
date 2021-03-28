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
		explicit CellReminder(Card* card, int id, QWidget *parent = nullptr);
		~CellReminder();

		void UpdateCard(Card* card);
		int GetId();

		Card GetCard();
	private:
		Ui::CellReminder *ui;

		int id = -1;
		Card card;

		void setWidgetData(Card* card);

		void setStartStatusIconAndLabel(QDateTime startDate);
		void setTypeIcon(bool isReminder);

		void setPriorityIcon(Card::Priority priority);
};

#endif // CELLREMINDER_H
