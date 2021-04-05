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

bool ReminderCard::IsEqual(const Card* other)
{
	const ReminderCard* remidnerCard = dynamic_cast<const ReminderCard*>(other);

	if(remidnerCard == nullptr)
	{
		return false;
	}

	bool result = Card::IsEqual(other);

	if(result && remindInterval == remidnerCard->remindInterval)
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
