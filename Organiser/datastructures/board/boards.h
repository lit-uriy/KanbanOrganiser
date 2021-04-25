#ifndef BOARDS_H
#define BOARDS_H

#include <QList>
#include "datastructures/board/board.h"

class Boards
{
public:
    Boards();
    QList<Board> boards;

    int GetSize();

    void AddBoard(Board board);
    void EditBoard();
    bool DeleteBoard(int index);

    Board* GetBoard(int index);//TODO:const

    Card* GetCardWithID(unsigned long long id) throw(GeneralException);
};

#endif // BOARDS_H
