#include "card.h"

Card::Card()
{

}

Card::Card(QString title, QString description, QDateTime creationDate)
{
	this->title = title;
	this->description = description;
	this->creationDate = creationDate;
}

bool Card::operator==(const Card &other)
{
	return isEqual(other);
}

bool Card::operator!=(const Card &other)
{
	return !isEqual(other);
}

bool Card::IsNull()
{
	if(title.isNull() || description.isNull() || creationDate.isNull())
	{
		return true;
	}

	return false;
}

bool Card::isEqual(const Card &other)
{
	if(this->title.compare(other.title) == 0 &&
			this->description.compare(other.description) == 0 &&
			this->creationDate == other.creationDate &&
			this->priority == priority &&
			this->status == status &&
			this->finishedDate == finishedDate)
	{
		return true;
	}

	return false;
}
