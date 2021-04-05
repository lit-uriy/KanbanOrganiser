#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QDateTime>

class Card
{
	public:

		Card();
		virtual ~Card();
		Card(Card* copy);
		Card(QByteArray data);
		Card(QString title, QString description, QDateTime creationDate);

		Card(QString title, QString description, QDateTime creationDate, QDateTime startDate,QDateTime deadline);

		virtual bool IsEqual(const Card* other);

		unsigned long long id = 0;

		QString title;
		QString description;

		enum class Priority {Low,Medium,High};
		Priority priority = Priority::Low;

		enum class Status {Started,Finished,Canceled};
		Status status = Status::Started;

		QDateTime creationDate;
		QDateTime finishedDate;

		QDateTime startDate;//Remind date for reminderCard
		QDateTime deadline;

		QDateTime postponedDeadline;
		virtual bool IsNull();

		QByteArray Encode();
		void SetDataFromArray(QByteArray data);

		QDateTime GetFinishingDate();
	private:
		unsigned long long generateId();

};

#endif // CARD_H
