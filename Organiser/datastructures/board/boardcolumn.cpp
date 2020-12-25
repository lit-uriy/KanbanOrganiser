#include "boardcolumn.h"

BoardColumn::BoardColumn()
{

}

BoardColumn::BoardColumn(QString title)
{
	this->title = title;
}

bool BoardColumn::operator==(const BoardColumn &other)
{
	return isEqual(other);
}

bool BoardColumn::operator!=(const BoardColumn &other)
{
	return !isEqual(other);
}

bool BoardColumn::isEqual(const BoardColumn &other)
{
	if(this->title.compare(other.title) == 0)
	{
		return true;
	}

	return false;
}

bool BoardColumn::IsNull()
{
	if(title.compare("") == 0 || title.isNull() || title.isEmpty())
	{
		return true;
	}

	return false;
}
