#include "card.h"

Card::Card(QString title, QString description, QDateTime creationDate)
{
	this->title = title;
	this->description = description;
	this->creationDate = creationDate;
}
