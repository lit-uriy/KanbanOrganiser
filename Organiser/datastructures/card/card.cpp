#include "card.h"

Card::Card()
{
	id = generateId();
}

Card::~Card()
{

}

unsigned long long Card::generateId()
{
	return QDateTime::currentMSecsSinceEpoch();
}

Card::Card(QByteArray data) : Card()
{
	SetDataFromArray(data);
}

Card::Card(Card* copy) : Card()
{
	this->id = copy->id;
	this->title = copy->title;
	this->description = copy->description;

	this->priority = copy->priority;
	this->status = copy->status;
    this->markedAsShown = copy->markedAsShown;

	this->creationDate = copy->creationDate;
	this->finishedDate = copy->finishedDate;

	this->startDate = copy->startDate;
	this->deadline = copy->deadline;
}

Card::Card(QString title, QString description, QDateTime creationDate, QDateTime startDate,QDateTime deadline) : Card(title,description,creationDate)
{
	this->startDate = startDate;
	this->deadline = deadline;
}

Card::Card(QString title, QString description, QDateTime creationDate) : Card()
{
	this->title = title;
	this->description = description;
	this->creationDate = creationDate;
}

bool Card::IsNull()
{
	if(title.isNull() || description.isNull() || creationDate.isNull())
	{
		return true;
	}

	return false;
}

QByteArray Card::Encode()
{
	QByteArray data;

	QString temp = QString::number(id);
	data.append(temp.length());
	data.append(temp);

	data.append((int)title.length());
	data.append(title);

	data.append((int)description.length());
	data.append(description);

	data.append((int)1);
	data.append((int)priority);

	data.append((int)1);
	data.append((int)status);

    data.append((int)1);
    data.append((int)markedAsShown);

	temp = creationDate.toString("yyyy-MM-dd hh:mm:ss");
	data.append((int)temp.length());
	data.append(temp);

	temp = finishedDate.toString("yyyy-MM-dd hh:mm:ss");
	data.append((int)temp.length());
	data.append(temp);

	temp = startDate.toString("yyyy-MM-dd hh:mm:ss");
	data.append((int)temp.length());
	data.append(temp);

	temp = deadline.toString("yyyy-MM-dd hh:mm:ss");
	data.append((int)temp.length());
	data.append(temp);

	return data;
}

void Card::SetDataFromArray(QByteArray data)
{
	int currentIndex = 0;

	int length = data.mid(0,1)[0];
	currentIndex += 1;
	id = data.mid(currentIndex,length).toULongLong();
	currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	title = data.mid(currentIndex,length);
	currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	description = data.mid(currentIndex,length);
	currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	priority = (Priority)data.mid(currentIndex,length).toInt();
	currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	status = (Status)data.mid(currentIndex,length).toInt();
	currentIndex += length;

    length = data.mid(currentIndex,1)[0];
    currentIndex += 1;
    markedAsShown = data.mid(currentIndex,length).toInt();
    currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	creationDate = QDateTime::fromString(QString(data.mid(currentIndex,length)),"yyyy-MM-dd hh:mm:ss");
	currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	finishedDate = QDateTime::fromString(QString(data.mid(currentIndex,length)),"yyyy-MM-dd hh:mm:ss");
	currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	startDate = QDateTime::fromString(QString(data.mid(currentIndex,length)),"yyyy-MM-dd hh:mm:ss");
	currentIndex += length;

	length = data.mid(currentIndex,1)[0];
	currentIndex += 1;
	deadline = QDateTime::fromString(QString(data.mid(currentIndex,length)),"yyyy-MM-dd hh:mm:ss");
	currentIndex += length;

}

QDateTime Card::GetFinishingDate()
{
	if(status == Status::Started)
	{
		return deadline;
	}
	else
	{
		return finishedDate;
	}
}

bool Card::IsEqual(const Card* other)
{
	if(this->title.compare(other->title) == 0 &&
			this->description.compare(other->description) == 0 &&
			this->creationDate == other->creationDate &&
			this->priority == other->priority &&
			this->status == other->status &&
            this->markedAsShown == other->markedAsShown &&
			this->finishedDate == other->finishedDate &&
			this->startDate == other->startDate &&
			this->deadline == other->deadline)
	{
		return true;
	}

	return false;
}

