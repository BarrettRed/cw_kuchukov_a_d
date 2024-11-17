#include "board.h"
#include "cell.h"
#include "pawn.h"
#include "queen.h"

bool Pawn::CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const
{
    int direction = this->GetColor() == Color::Black ? 1 : -1;

    if (this->IsFirstMove() && (from_cell->y_ + direction * 2 == to_cell->y_) && (from_cell->x_ == to_cell->x_))
        return board->IsEmptyVertical(from_cell, to_cell) && to_cell->IsEmpty();

    if (from_cell->y_ + direction == to_cell->y_) {
        if ((from_cell->x_ == to_cell->x_) && to_cell->IsEmpty())
            return true;
        if ((abs(from_cell->x_ - to_cell->x_) == 1) && from_cell->IsEnemy(to_cell))
            return true;
    }   
    
    return false;
}

void Pawn::MoveFigure(Cell* current, Cell* target, Board* board) {
    Piece::MoveFigure(current, target, board);
    if (GetColor() == Color::White && target->y_ == 0) {
        target->DeletePiece();
        target->SetPiece(new Queen(Color::White));
    }
    if (GetColor() == Color::Black && target->y_ == 7) {
        target->DeletePiece();
        target->SetPiece(new Queen(Color::Black));
    }
}

Piece* Pawn::GetCopy() const
{
    return new Pawn(*this);
}
