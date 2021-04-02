#include "reminders.h"

Reminders::Reminders()
{

}

Reminders Reminders::CreateInvalid()
{
    Reminders reminders;
    reminders.valid = false;
    return reminders;
}

void Reminders::AddCard(ReminderCard* card)
{
    cards.append(card);
}

void Reminders::AddCardAt(int index, ReminderCard* card)
{
    if(index < 0 || index > cards.size())
    {
        throw GeneralException("Index out of range");
        return;
    }

    cards.insert(index,card);
}

int Reminders::Find(ReminderCard* card)
{
    for(int i=0; i < cards.size();i++)
    {
        if(card == cards.at(i))
        {
            return i;
        }
    }

    return -1;
}

int Reminders::GetCardsCount()
{
    return cards.size();
}

QList<ReminderCard*> Reminders::GetCards()
{
    return cards;
}

ReminderCard* Reminders::GetCard(unsigned long long id) const throw(GeneralException)
{
	int index = findCardIndex(id);
	if(index < 0 || index >= cards.size())
	{
		throw GeneralException("Index out of range");
		return nullptr;
	}

	return cards[index];
}

ReminderCard* Reminders::GetCardAt(int index) const throw(GeneralException)
{
	if(index < 0 || index >= cards.size())
	{
		throw GeneralException("Index out of range");
		return nullptr;
	}
    return cards[index];
}

void Reminders::DeleteCard(unsigned long long id) throw(GeneralException)
{
	int index = findCardIndex(id);
	if(index < 0 || index >= cards.size())
    {
        throw GeneralException("Index out of range");
        return;
	}

	cards.removeAt(index);
}

int Reminders::findCardIndex(unsigned long long id) const
{
	for(int i=0; i < cards.size();i++)
	{
		if(id == cards.at(i)->id)
		{
			return i;
		}
	}

	return -1;
}

void Reminders::ReplaceCard(unsigned long long id, ReminderCard* card) throw(GeneralException)
{
	int index = findCardIndex(id);
	if(index < 0 || index >= cards.size())
	{
		throw GeneralException("Index out of range");
		return;
	}

    cards.replace(index,card);
}
