#include "board.h"
#include "cell.h"
#include "king.h"

bool King::CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const
{
    if (!Piece::CanMove(from_cell, to_cell, board))
        return false;
    
    int diff_x = abs(from_cell->x_ - to_cell->x_);
    int diff_y = abs(from_cell->y_ - to_cell->y_);
   
    if (diff_x <= 1 && diff_y <= 1) {
        Board tmp_board(*board);
        Cell* tmp_from_cell = tmp_board.GetCell(from_cell->x_, from_cell->y_);
        Cell* tmp_to_cell = tmp_board.GetCell(to_cell->x_, to_cell->y_);
        tmp_board.MoveFigure(tmp_from_cell, tmp_to_cell);
        return !tmp_board.IsCellUnderAttack(tmp_to_cell, tmp_board.GetCurrentPlayerColor());
    } 

    if (IsFirstMove() && diff_y == 0) {
        Piece* piece(nullptr);
        Cell* rook_cell = board->GetCell(0, from_cell->y_);
        if (from_cell->x_ - to_cell->x_ == 2 && board->IsEmptyHorizontal(from_cell, rook_cell)) {
            piece = rook_cell->GetPiece();
            if (piece && piece->GetPieceName() == Piece::PieceName::Rook && piece->IsFirstMove())
                return true;
        }
        rook_cell = board->GetCell(7, from_cell->y_);
        if (from_cell->x_ - to_cell->x_ == -2 && board->IsEmptyHorizontal(from_cell, rook_cell)) {
            piece = rook_cell->GetPiece();
            if (piece && piece->GetPieceName() == Piece::PieceName::Rook && piece->IsFirstMove())
                return true;
        }
    }

    return false;
}

Piece* King::GetCopy() const
{
    return new King(*this);
}

void King::MoveFigure(Cell* current, Cell* target, Board* board)
{
    Piece::MoveFigure(current, target, board);
    if (current->x_ - target->x_ == 2) {
        board->MoveFigure(board->GetCell(0, current->y_), board->GetCell(3, current->y_),  Piece::PieceMove::Castling);
    }
    if (current->x_ - target->x_ == -2) {
        board->MoveFigure(board->GetCell(7, current->y_), board->GetCell(5, current->y_), Piece::PieceMove::Castling);
    }
}
