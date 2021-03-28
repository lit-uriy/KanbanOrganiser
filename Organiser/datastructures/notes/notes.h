#ifndef NOTES_H
#define NOTES_H

#include <QList>
#include "datastructures/card/card.h"
#include "exceptions/generalexception.h"

class Notes
{
	public:
		Notes();

		static Notes CreateInvalid();

		void AddCard(Card* card);
		void AddCardAt(int index, Card* card);

		int Find(Card* card);

		int GetCardsCount();

		QList<Card*> GetCards();

		Card* GetCardAt(int index) const throw(GeneralException);

		void DeleteCard(int index) throw(GeneralException);

		void ReplaceCard(int index, Card* card) throw(GeneralException);

		bool IsValid(){return valid;}
	protected:
		QList<Card*> cards;

		bool valid = true;
};

#endif // NOTES_H
