#include "board.h"
#include "cell.h"
#include "knight.h"
#include <iostream>
bool Knight::CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const
{
    if (!Piece::CanMove(from_cell, to_cell, board))
        return false;

    int diff_x = abs(from_cell->x_ - to_cell->x_);
    int diff_y = abs(from_cell->y_ - to_cell->y_);
    // std::cout << from_cell->x_ << ' ' << from_cell->y_ << ' ' << to_cell->x_ << ' ' << to_cell->y_;
    return (diff_x == 1 && diff_y == 2) || (diff_x == 2 && diff_y == 1);
}

Piece* Knight::GetCopy() const
{
    return new Knight(*this);
}
