#ifndef REMINDERCARD_H
#define REMINDERCARD_H

#include "datastructures/card/card.h"

enum class RemindInterval
{
	None = 0,
	Daily,
	Weekly,
	Monthly
};

class ReminderCard : public Card
{
	public:
		//TODO:Add Card Icon
		ReminderCard();
		ReminderCard(Card* copy);
		ReminderCard(QString title, QString description, QDateTime creationDate);
		RemindInterval remindInterval = RemindInterval::None;


		bool IsNull() override;
		bool operator==(const ReminderCard &other);
		bool operator!=(const ReminderCard &other);
};

#endif // REMINDERCARD_H
