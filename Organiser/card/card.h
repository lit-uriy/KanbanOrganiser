#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QDateTime>

class Card
{
	public:
		Card(QString title, QString description, QDateTime creationDate);

		QString title;
		QString description;

		int status;

		QDateTime creationDate;
		QDateTime finishedDate;
};

#endif // CARD_H
