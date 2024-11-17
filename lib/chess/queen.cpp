#include "board.h"
#include "cell.h"
#include "queen.h"

bool Queen::CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const
{
    if (!Piece::CanMove(from_cell, to_cell, board))
        return false;

    if (board->IsEmptyDiagonal(from_cell, to_cell))
        return true;

    if (board->IsEmptyHorizontal(from_cell, to_cell))
        return true;

    if (board->IsEmptyVertical(from_cell, to_cell))
        return true;

    return false;
}

Piece* Queen::GetCopy() const
{
    return new Queen(*this);
}
