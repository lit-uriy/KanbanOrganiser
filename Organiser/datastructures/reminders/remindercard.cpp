#include "remindercard.h"

ReminderCard::ReminderCard()
{

}

bool ReminderCard::operator==(const ReminderCard &other)
{
	bool result = Card::operator==(other);

	if(result && remindInterval == other.remindInterval)
	{
		return true;
	}

	return false;
}

bool ReminderCard::operator!=(const ReminderCard &other)
{
	bool result = Card::operator!=(other);

	if(result && remindInterval != other.remindInterval)
	{
		return true;
	}

	return false;
}

bool ReminderCard::IsNull()
{
	if(title.isNull())
	{
		return true;
	}

	return false;
}
