#include "appdata.h"

AppData::AppData()
{

}


bool AppData::IsValid()
{
	if(!notes.IsValid())
	{
		return false;
	}

	return true;
}


const Card* AppData::FindCard(unsigned long long id)
{
	return findCard(id);
}

Card* AppData::findCard(unsigned long long id)
{
	Card* card = reminders.GetCard(id);
	if(card != nullptr)
	{
		return card;
	}

    card = notes.GetCardWithID(id);
    if(card != nullptr)
    {
        return card;
    }

    card = boards.GetCardWithID(id);
    if(card != nullptr)
    {
        return card;
    }

	return nullptr;
}

void AppData::MarkCardAsShown(unsigned long long id)
{
	Card* card = findCard(id);

	if(card != nullptr)
	{
        card->markedAsShown = true;
	}
}

void AppData::PostponeCard(unsigned long long id,int timeInMinutes)
{
	Card* card = findCard(id);

	if(card != nullptr)
	{
		card->postponedDeadline = QDateTime::currentDateTime().addSecs(60*timeInMinutes);
	}
}
