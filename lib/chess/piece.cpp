#include "board.h"
#include "cell.h"
#include "piece.h"

bool Piece::CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const
{
    return to_cell->IsEmpty() || from_cell->IsEnemy(to_cell);
}

Piece::PieceName Piece::GetPieceName() const
{
    return name_;
}

Color Piece::GetColor() const
{
    return color_;
}

bool Piece::IsFirstMove() const
{
    return is_first_move_;
}

void Piece::SetFirstMove(bool is_fisrt_move)
{
    is_first_move_ = is_fisrt_move;
}

void Piece::MoveFigure(Cell* current, Cell* target, Board* board)
{
    is_first_move_ = false;
}
