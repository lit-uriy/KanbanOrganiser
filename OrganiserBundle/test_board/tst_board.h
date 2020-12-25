#ifndef TST_BOARD_H
#define TST_BOARD_H

#include <QtTest>

// add necessary includes here
#include "datastructures/board/board.h"

class test_board : public QObject
{
		Q_OBJECT

	public:
		test_board();
		~test_board();

	private slots:
		void addColumnToBoard();
		void getColumnOutOfRangeException();
		void deleteColumnFromBoard();
		void editColumnNameInBoard();
		void addCardToColumnInBoard();
		void replaceCardInColumnInBoard();
		void deleteCardFromColumnInBoard();
		void moveCardToOtherColumnInSameBoard();

};


#endif // TST_BOARD_H
