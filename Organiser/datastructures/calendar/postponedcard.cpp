#include "postponedcard.h"

PostponedCard::PostponedCard(unsigned long long id, int minutes)
{
	this->Id = id;
	this->Minutes = minutes;
}

bool PostponedCard::operator==( const PostponedCard& other)
{
	return this->Id == other.Id;
}
