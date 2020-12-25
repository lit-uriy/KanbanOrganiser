#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QDateTime>

class Card
{
	public:
		Card();
		Card(QString title, QString description, QDateTime creationDate);

		bool operator==(const Card &other);
		bool operator!=(const Card &other);

		QString title;
		QString description;

		enum class Priority {Low,Medium,High};
		Priority priority = Priority::Low;

		enum class Status {Started,Finished,Canceled};
		Status status = Status::Started;

		QDateTime creationDate;
		QDateTime finishedDate;

		bool IsNull();
	private:
		bool isEqual(const Card &other);
};

#endif // CARD_H
