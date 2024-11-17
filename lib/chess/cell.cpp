#include "cell.h"
#include "piece.h"


Cell::~Cell()
{
    delete piece_;
}

Piece* Cell::GetPiece() const
{
    return piece_;
}

Color Cell::GetColor() const
{
    return color_;
}

bool Cell::IsEnemy(const Cell* target) const
{
    return !target->IsEmpty() && this->GetPiece()->GetColor() != target->GetPiece()->GetColor();
}

bool Cell::IsEmpty() const
{
    return piece_ == nullptr;
}

void Cell::DeletePiece()
{
    if (piece_)
        delete piece_;
    piece_ = nullptr;
}

void Cell::SetPiece(Piece* piece)
{
    piece_ = piece;
}

bool Cell::IsAvailable() const
{
    return is_available_;
}

void Cell::SetAvailable(bool available)
{
    is_available_ = available;
}
