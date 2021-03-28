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

ReminderCard* Reminders::GetCardAt(int index) const throw(GeneralException)
{
    if(index < 0 || index >= cards.size())
    {
        throw GeneralException("Index out of range");
        return nullptr;
    }
    return cards[index];
}

void Reminders::DeleteCard(int index) throw(GeneralException)
{
    if(index < 0 || index >= cards.size())
    {
        throw GeneralException("Index out of range");
        return;
    }
    cards.removeAt(index);
}


void Reminders::ReplaceCard(int index, ReminderCard* card) throw(GeneralException)
{
    if(index < 0 || index >= cards.size())
    {
        throw GeneralException("Index out of range");
        return;
    }

    cards.replace(index,card);
}
