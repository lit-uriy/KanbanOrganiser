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

		void AddCard(ReminderCard* card);
		void AddCardAt(int index, ReminderCard* card);

		int Find(ReminderCard* card);

		int GetCardsCount();

		QList<ReminderCard*> GetCards();

		ReminderCard* GetCard(unsigned long long id) const throw(GeneralException);
		ReminderCard* GetCardAt(int index) const throw(GeneralException);

		void DeleteCard(unsigned long long id) throw(GeneralException);

		void ReplaceCard(unsigned long long id, ReminderCard* card) throw(GeneralException);

		bool IsValid(){return valid;}
	protected:
		QList<ReminderCard*> cards;

		int findCardIndex(unsigned long long id) const;
		bool valid = true;
};

#endif // REMINDERS_H
