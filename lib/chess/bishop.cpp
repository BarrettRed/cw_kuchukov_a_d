#include "board.h"
#include "bishop.h"
#include "cell.h"


bool Bishop::CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const
{
    if (!Piece::CanMove(from_cell, to_cell, board))
        return false;

    if (board->IsEmptyDiagonal(from_cell, to_cell))
        return true;
    
    return false;
}

Piece* Bishop::GetCopy() const
{
    return new Bishop(*this);
}
