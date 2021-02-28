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
		ReminderCard();

		RemindInterval remindInterval = RemindInterval::None;


		bool operator==(const ReminderCard &other);
		bool operator!=(const ReminderCard &other);
};

#endif // REMINDERCARD_H
