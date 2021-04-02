#include "remindercard.h"

ReminderCard::ReminderCard() : Card()
{

}

ReminderCard::ReminderCard(Card* copy) : Card(copy)
{
	ReminderCard* reminderCard = dynamic_cast<ReminderCard*>(copy);
	if(reminderCard != nullptr)
	{
		this->remindInterval = reminderCard->remindInterval;
	}
}

ReminderCard::ReminderCard(QString title, QString description, QDateTime creationDate) : Card(title,description,creationDate)
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
