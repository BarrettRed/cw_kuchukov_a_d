#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#define private \
  public  // ��� ������������ �������� ������� � ����� (�� ������������� �
          // �������� ��������).

#include "board.h"
#include "cell.h"
#include "piece.h"  // ���� ���� ������� ����� �����.

TEST_CASE("Chess lib test") {
  Board* board = new Board();

  SUBCASE("Board initialization") {
    board->InitBoard();

    // ��������, ��� ����� �� ����� � �������� ��������� ������������ �����.
    CHECK(board->GetCell(0, 0)->GetPiece() != nullptr);  // �����
    CHECK(board->GetCell(0, 0)->GetPiece()->GetPieceName() == Piece::PieceName::Rook);
    
    // ��������, ��� ����� ��������� �� ������ � ������������� ������.
    for (int i = 0; i < 8; ++i) {
      Piece* piece = board->GetCell(i, 1)->GetPiece();
      CHECK(piece != nullptr);
      CHECK(piece->GetPieceName() == Piece::PieceName::Pawn);
      CHECK(piece->GetColor() == Color::Black);
      piece = board->GetCell(i, 6)->GetPiece();
      CHECK(piece != nullptr);
      CHECK(piece->GetPieceName() == Piece::PieceName::Pawn);
      CHECK(piece->GetColor() == Color::White);
    }

    // ��������, ��� ������ ������ ������������� �����.
    for (int row = 2; row <= 5; ++row) {
      for (int col = 0; col < 8; ++col) {
        CHECK(board->GetCell(col, row)->GetPiece() == nullptr);
      }
    }
  }

  SUBCASE("Move validation") {
    board->InitBoard();
    Cell* from_cell = board->GetCell(1, 6);
    Cell* to_cell = board->GetCell(1, 4);
    Piece* piece = board->GetCell(1, 6)->GetPiece();
    
    CHECK(piece->CanMove(from_cell, to_cell, board));  // ����� � (1, 6) �� (1, 4).
    
    to_cell = board->GetCell(1, 5);
    CHECK(piece->CanMove(from_cell, to_cell, board));  // ����� � (1, 6) �� (5, 1).

    to_cell = board->GetCell(1, 3);
    CHECK_FALSE(piece->CanMove(from_cell, to_cell, board));  // ����� � (1, 6) �� (1, 3).
  }

  SUBCASE("Castling && Turning pawn into queen") {
    board->InitBoard();
    CHECK(board->GetCell(6, 7)->GetPiece()->CanMove(board->GetCell(6, 7), board->GetCell(7, 5), board)); // ���� � (6, 7) �� (7, 5).
    board->MoveFigure(board->GetCell(6, 7), board->GetCell(7, 5));
    board->MoveFigure(board->GetCell(1, 1), board->GetCell(1, 3));
    board->MoveFigure(board->GetCell(6, 6), board->GetCell(6, 5));
    board->MoveFigure(board->GetCell(1, 3), board->GetCell(1, 4));
    CHECK(board->GetCell(5, 7)->GetPiece()->CanMove(board->GetCell(5, 7), board->GetCell(6, 6), board)); // ���� � (5, 7) �� (6, 6).
    board->MoveFigure(board->GetCell(5, 7), board->GetCell(6, 6));
    board->MoveFigure(board->GetCell(1, 4), board->GetCell(1, 5));
    CHECK(board->GetCell(4, 7)->GetPiece()->CanMove(board->GetCell(4, 7), board->GetCell(6, 7), board)); // ���������.
    board->MoveFigure(board->GetCell(4, 7), board->GetCell(6, 7));
    CHECK(board->GetCell(5, 7)->GetPiece()->GetPieceName() == Piece::PieceName::Rook); // ����� ����� ���������.
    board->MoveFigure(board->GetCell(1, 5), board->GetCell(2, 6));
    board->MoveFigure(board->GetCell(6, 6), board->GetCell(0, 0));
    board->MoveFigure(board->GetCell(2, 6), board->GetCell(3, 7));
    CHECK(board->GetCell(3, 7)->GetPiece()->GetPieceName() == Piece::PieceName::Queen); // ����� �������� �� ��������.
  }
}
