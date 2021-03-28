#include "board.h"

Board::Board()
{

}

void Board::AddColumn(BoardColumn column)
{
    columns.append(column);
}

void Board::EditColumnName(int index, QString title) throw(GeneralException)
{
    if(index < 0 || index >= columns.size())
    {
        throw GeneralException("Index out of range");
        return;
    }

    columns[index].title = title;
}

BoardColumn Board::GetColumnAt(int index) throw(GeneralException)
{
    if(index < 0 || index >= columns.size())
    {
        throw GeneralException("Index out of range");
        return BoardColumn();
    }

    return columns.at(index);
}

int Board::GetColumnCount()
{
    return columns.size();
}

void Board::DeleteColumn(int index) throw(GeneralException)
{
    if(index < 0 || index >= columns.size())
    {
        throw GeneralException("Index out of range");
        return;
    }

    columns.removeAt(index);
}

void Board::AddCardToColumn(int columnIndex, Card* card) throw(GeneralException)
{
    if(columnIndex < 0 || columnIndex >= columns.size())
    {
        throw GeneralException("Index out of range");
        return;
    }

    columns[columnIndex].AddCard(card);
}

void Board::ReplaceCardInColumn(int columnIndex, int cardIndex, Card* card) throw(GeneralException)
{
    if(columnIndex < 0 || columnIndex >= columns.size())
    {
        throw GeneralException("Index out of range");
        return;
    }

    columns[columnIndex].ReplaceCard(cardIndex,card);
}

void Board::DeleteCardFromColumn(int columnIndex, int cardIndex) throw(GeneralException)
{
    if(columnIndex < 0 || columnIndex >= columns.size())
    {
        throw GeneralException("Index out of range");
        return;
    }

    columns[columnIndex].DeleteCard(cardIndex);
}

void Board::MoveCard(int columnFrom,int cardIndex,int columnTo) throw(GeneralException)
{
    if(columnFrom < 0 || columnTo >= columns.size()
            || columnTo < 0 || columnTo >= columns.size())
    {
        throw GeneralException("Index out of range");
        return;
    }


    Card* card = columns.at(columnFrom).GetCardAt(cardIndex);

    columns[columnFrom].DeleteCard(cardIndex);

    columns[columnTo].AddCard(card);

}
