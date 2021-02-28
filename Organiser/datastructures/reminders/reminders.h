#ifndef REMINDERS_H
#define REMINDERS_H

#include <QList>
#include "remindercard.h"
#include "exceptions/generalexception.h"

class Reminders
{
	public:
		Reminders();

		static Reminders CreateInvalid();

		void AddCard(ReminderCard card);
		void AddCardAt(int index, ReminderCard card);

		int Find(ReminderCard card);

		int GetCardsCount();

		QList<ReminderCard> GetCards();

		ReminderCard GetCardAt(int index) const throw(GeneralException);

		void DeleteCard(int index) throw(GeneralException);

		void ReplaceCard(int index, ReminderCard card) throw(GeneralException);

		bool IsValid(){return valid;}
	protected:
		QList<ReminderCard> cards;

		bool valid = true;
};

#endif // REMINDERS_H
