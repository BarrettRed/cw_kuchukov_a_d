#include "board.h"
#include "cell.h"
#include "rook.h"

bool Rook::CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const
{
    if (!Piece::CanMove(from_cell, to_cell, board))
        return false;

    if (board->IsEmptyHorizontal(from_cell, to_cell))
        return true;

    if (board->IsEmptyVertical(from_cell, to_cell))
        return true;

    return false;
}

Piece* Rook::GetCopy() const
{
    return new Rook(*this);
}
