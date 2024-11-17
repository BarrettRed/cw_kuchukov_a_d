#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#define private \
  public  // Для тестирования закрытых методов и полей (не рекомендуется в
          // реальных проектах).

#include "board.h"
#include "cell.h"
#include "piece.h"  // Если есть базовый класс фигур.

TEST_CASE("Chess lib test") {
  Board* board = new Board();

  SUBCASE("Board initialization") {
    board->InitBoard();

    // Проверим, что доска не пуста и содержит начальное расположение фигур.
    CHECK(board->GetCell(0, 0)->GetPiece() != nullptr);  // Ладья
    CHECK(board->GetCell(0, 0)->GetPiece()->GetPieceName() == Piece::PieceName::Rook);
    
    // Проверим, что пешки находятся на второй и предпоследней линиях.
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

    // Проверим, что пустые клетки действительно пусты.
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
    
    CHECK(piece->CanMove(from_cell, to_cell, board));  // Пешка с (1, 6) на (1, 4).
    
    to_cell = board->GetCell(1, 5);
    CHECK(piece->CanMove(from_cell, to_cell, board));  // Пешка с (1, 6) на (5, 1).

    to_cell = board->GetCell(1, 3);
    CHECK_FALSE(piece->CanMove(from_cell, to_cell, board));  // Пешка с (1, 6) на (1, 3).
  }

  SUBCASE("Castling && Turning pawn into queen") {
    board->InitBoard();
    CHECK(board->GetCell(6, 7)->GetPiece()->CanMove(board->GetCell(6, 7), board->GetCell(7, 5), board)); // Конь с (6, 7) на (7, 5).
    board->MoveFigure(board->GetCell(6, 7), board->GetCell(7, 5));
    board->MoveFigure(board->GetCell(1, 1), board->GetCell(1, 3));
    board->MoveFigure(board->GetCell(6, 6), board->GetCell(6, 5));
    board->MoveFigure(board->GetCell(1, 3), board->GetCell(1, 4));
    CHECK(board->GetCell(5, 7)->GetPiece()->CanMove(board->GetCell(5, 7), board->GetCell(6, 6), board)); // Слон с (5, 7) на (6, 6).
    board->MoveFigure(board->GetCell(5, 7), board->GetCell(6, 6));
    board->MoveFigure(board->GetCell(1, 4), board->GetCell(1, 5));
    CHECK(board->GetCell(4, 7)->GetPiece()->CanMove(board->GetCell(4, 7), board->GetCell(6, 7), board)); // Рокировка.
    board->MoveFigure(board->GetCell(4, 7), board->GetCell(6, 7));
    CHECK(board->GetCell(5, 7)->GetPiece()->GetPieceName() == Piece::PieceName::Rook); // Ладья после рокировки.
    board->MoveFigure(board->GetCell(1, 5), board->GetCell(2, 6));
    board->MoveFigure(board->GetCell(6, 6), board->GetCell(0, 0));
    board->MoveFigure(board->GetCell(2, 6), board->GetCell(3, 7));
    CHECK(board->GetCell(3, 7)->GetPiece()->GetPieceName() == Piece::PieceName::Queen); // Пешку поменяли на королеву.
  }
}
