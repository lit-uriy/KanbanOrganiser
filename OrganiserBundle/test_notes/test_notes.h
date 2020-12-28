#ifndef TEST_NOTES_H
#define TEST_NOTES_H

#include <QtTest>

class test_notes : public QObject
{
		Q_OBJECT

	public:
		test_notes();
		~test_notes();

	private slots:
		void addCardToNotes();
		void addCardToNotesAtPosition();
		void getCardOutOfRangeException();
		void deleteCardFromNotes();
		void editCardInNotes();

};

#endif // TEST_NOTES_H
