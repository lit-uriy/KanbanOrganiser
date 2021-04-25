#include "boards.h"

Boards::Boards()
{

}

int Boards::GetSize()
{
   return boards.size();
}

Board* Boards::GetBoard(int index)
{
    if(index < 0 || index >= boards.size())
    {
        throw GeneralException("Index out of range");
        return nullptr;
    }
    return &boards[index];
}

void Boards::AddBoard(Board board)
{
    boards.append(board);
}

bool Boards::DeleteBoard(int index)
{
    if(index < 0 || index >= boards.size())
    {
        throw GeneralException("Index out of range");
        return false;
    }

    boards.removeAt(index);

    return true;
}

Card* Boards::GetCardWithID(unsigned long long id) throw(GeneralException)
{
    for(int i=0; i < boards.size();i++)
    {
        for(int j=0; j <  boards[i].GetColumnCount();j++)
        {
            Card * card = boards[i].GetColumnAt(j)->GetCardWithID(id);

            if(card != nullptr)
            {
                return card;
            }
        }
    }

    throw GeneralException("Can't find card with requested ID");
    return nullptr;
}
