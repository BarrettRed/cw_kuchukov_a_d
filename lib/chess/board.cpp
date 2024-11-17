#include "board.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include <iostream>

Board::Board(const Board& other) : current_player_(other.current_player_), winner_(other.winner_) {
    for (int i = 0; i < 8; ++i) 
        for (int j = 0; j < 8; ++j) 
            cells_[i][j] = new Cell(*other.cells_[i][j]);
}

Board::Board() : current_player_(Color::White), winner_(Color::None)
{
    for (size_t i = 0; i < 8; i++) 
        for (size_t j = 0; j < 8; j++) 
            cells_[i][j] = new Cell(j, i, ((i + j) % 2 == 0) ? Color::White : Color::Black, nullptr);
}

Board::~Board()
{
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            delete cells_[i][j];
}

void Board::ClearBoard()
{
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            cells_[i][j]->DeletePiece();
    DropAvailableMoves();
}

Piece* Board::CreatePiece(Piece::PieceName name, Color color, bool is_first_move) const
{
    Piece* piece(nullptr);
    switch (name) {
    case Piece::PieceName::Bishop:
        piece = new Bishop(color);
        break;
    case Piece::PieceName::King:
        piece = new King(color);
        break;
    case Piece::PieceName::Knight:
        piece = new Knight(color);
        break;
    case Piece::PieceName::Pawn:
        piece = new Pawn(color);
        break;
    case Piece::PieceName::Queen:
        piece = new Queen(color);
        break;
    case Piece::PieceName::Rook:
        piece = new Rook(color);
        break;
    }
    piece->SetFirstMove(is_first_move);
    return piece;
}

void Board::SetPiece(Piece* piece, int row, int col)
{
    cells_[row][col]->SetPiece(piece);
}

Cell* Board::GetCell(int x, int y) const
{
    return cells_[y][x];
}

Color Board::GetCurrentPlayerColor() const 
{
    return current_player_;
}

void Board::SetCurrentPlayerColor(Color color)
{
    current_player_ = color;
}

Color Board::GetWinner() const 
{
    return winner_;
}

void Board::InitBoard()
{ 
    ClearBoard();
    AddPieces();
}

bool Board::IsEmptyDiagonal(const Cell* from_cell, const Cell* to_cell) const
{
    int diff_x = abs(from_cell->x_ - to_cell->x_);
    int diff_y = abs(from_cell->y_ - to_cell->y_);
    
    if (diff_x != diff_y)
        return false;

    int dx = from_cell->x_ < to_cell->x_ ? 1 : -1;
    int dy = from_cell->y_ < to_cell->y_ ? 1 : -1;
    for (int i = 1; i < diff_x; i++)
        if (!this->GetCell(from_cell->x_ + dx * i, from_cell->y_ + dy * i)->IsEmpty())
            return false;

    return true;
}

bool Board::IsEmptyHorizontal(const Cell* from_cell, const Cell* to_cell) const
{
    if (from_cell->y_ != to_cell->y_)
        return false;

    int min = std::min(from_cell->x_, to_cell->x_);
    int max = std::max(from_cell->x_, to_cell->x_);
    for (int x = min + 1; x < max; x++)
        if (!this->GetCell(x, from_cell->y_)->IsEmpty())
            return false;

    return true;
}

bool Board::IsEmptyVertical(const Cell* from_cell, const Cell* to_cell) const
{
    if (from_cell->x_ != to_cell->x_)
        return false;

    int min = std::min(from_cell->y_, to_cell->y_);
    int max = std::max(from_cell->y_, to_cell->y_);
    for (int y = min + 1; y < max; y++)
        if (!this->GetCell(from_cell->x_, y)->IsEmpty())
            return false;

    return true;
}

bool Board::IsCellUnderAttack(const Cell* cell, Color attacking_player) const {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            Piece* piece = cells_[i][j]->GetPiece();
            if (piece && piece->GetColor() == attacking_player) {
                if (piece->GetPieceName() == Piece::PieceName::King) {
                    // std::cout << i << " " << j << std::endl;
                    if (abs(j - cell->x_) <= 1 && abs(i - cell->y_) <= 1)
                        return true;
                }
                if (piece->CanMove(cells_[i][j], cell, this)) {
                    // std::cout << i << " " << j << std::endl;
                    return true;
                }
            }
        }
    return false;
}

bool Board::IsCheck(Color king_color) const {
    Cell* king_cell = FindKing(king_color);
    if (king_cell)
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) 
                if (IsCellUnderAttack(king_cell, king_color == Color::White ? Color::Black : Color::White))
                    return true;
    return false;
}

Cell* Board::FindKing(Color king_color) const {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            Piece* piece = cells_[i][j]->GetPiece();
            if (piece  && piece->GetColor() == king_color && piece->GetPieceName() == Piece::PieceName::King)
                return cells_[i][j];
        }
    return nullptr;
}

void Board::MoveFigure(Cell* from_cell, Cell* to_cell, Piece::PieceMove move)
{
    if (from_cell->GetPiece()->GetColor() == current_player_) {
        if (!to_cell->IsEmpty())
            if (to_cell->GetPiece()->GetPieceName() == Piece::PieceName::King)
                winner_ = from_cell->GetPiece()->GetColor();
            to_cell->DeletePiece();
        to_cell->SetPiece(from_cell->GetPiece());
        to_cell->GetPiece()->MoveFigure(from_cell, to_cell, this);
        from_cell->SetPiece(nullptr);
        if (move == Piece::PieceMove::Common)
            current_player_ = current_player_ == Color::White ? Color::Black : Color::White;
    }
}

void Board::SetAvailableMoves(const Cell* selected_cell) const
{
    Piece* selected_piece = selected_cell->GetPiece();
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            cells_[i][j]->SetAvailable(selected_piece->CanMove(selected_cell, cells_[i][j], this));

}

void Board::DropAvailableMoves() {
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            cells_[i][j]->SetAvailable(false);
}

void Board::Restart()
{
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            cells_[i][j]->DeletePiece();
    current_player_ = Color::White;
    winner_ = Color::None;
    this->InitBoard();
}

void Board::AddPieces()
{
    AddBishops();
    AddKings();
    AddKnights();
    AddPawns();
    AddQueens();
    AddRooks();
}

void Board::AddBishops()
{
    GetCell(2, 0)->SetPiece(new Bishop(Color::Black));
    GetCell(5, 0)->SetPiece(new Bishop(Color::Black));
    GetCell(2, 7)->SetPiece(new Bishop(Color::White));
    GetCell(5, 7)->SetPiece(new Bishop(Color::White));
}

void Board::AddKings()
{
    GetCell(4, 0)->SetPiece(new King(Color::Black));
    GetCell(4, 7)->SetPiece(new King(Color::White));
}

void Board::AddKnights()
{
    GetCell(1, 0)->SetPiece(new Knight(Color::Black));
    GetCell(6, 0)->SetPiece(new Knight(Color::Black));
    GetCell(1, 7)->SetPiece(new Knight(Color::White));
    GetCell(6, 7)->SetPiece(new Knight(Color::White));
}

void Board::AddPawns()
{
    for (int i = 0; i < 8; i++) {
        GetCell(i, 1)->SetPiece(new Pawn(Color::Black));
        GetCell(i, 6)->SetPiece(new Pawn(Color::White));
    }
}

void Board::AddQueens()
{
    GetCell(3, 0)->SetPiece(new Queen(Color::Black));
    GetCell(3, 7)->SetPiece(new Queen(Color::White));
}

void Board::AddRooks()
{
    GetCell(0, 0)->SetPiece(new Rook(Color::Black));
    GetCell(7, 0)->SetPiece(new Rook(Color::Black));
    GetCell(0, 7)->SetPiece(new Rook(Color::White));
    GetCell(7, 7)->SetPiece(new Rook(Color::White));
}
