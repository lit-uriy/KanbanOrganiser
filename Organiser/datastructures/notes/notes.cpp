#include "notes.h"


Notes::Notes()
{

}

Notes Notes::CreateInvalid()
{
	Notes notes;
	notes.valid = false;
	return notes;
}

void Notes::AddCard(Card card)
{
	cards.append(card);
}

void Notes::AddCardAt(int index, Card card)
{
	if(index < 0 || index > cards.size())
	{
		throw GeneralException("Index out of range");
		return;
	}

	cards.insert(index,card);
}

int Notes::Find(Card card)
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

int Notes::GetCardsCount()
{
	return cards.size();
}

QList<Card> Notes::GetCards()
{
	return cards;
}

Card Notes::GetCardAt(int index) const throw(GeneralException)
{
	if(index < 0 || index >= cards.size())
	{
		throw GeneralException("Index out of range");
		return Card();
	}
	return cards.at(index);
}

void Notes::DeleteCard(int index) throw(GeneralException)
{
	if(index < 0 || index >= cards.size())
	{
		throw GeneralException("Index out of range");
		return;
	}
	cards.removeAt(index);
}


void Notes::ReplaceCard(int index, Card card) throw(GeneralException)
{
	if(index < 0 || index >= cards.size())
	{
		throw GeneralException("Index out of range");
		return;
	}

	cards.replace(index,card);
}
