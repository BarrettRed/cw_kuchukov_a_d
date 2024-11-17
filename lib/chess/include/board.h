#pragma once

#include <array>
#include "cell.h"

/**
 * @brief Класс Board представляет шахматную доску и управляет ее состоянием.
 */
class Board {
public:
    /**
     * @brief Конструктор по умолчанию, инициализирующий шахматную доску.
     */
    Board();

    /**
     * @brief Конструктор копирования для создания копии другой доски.
     * @param other Другая доска для копирования.
     */
    Board(const Board& other);

    /**
     * @brief Деструктор, освобождающий память, выделенную для клеток и фигур.
     */
    ~Board();

    /**
     * @brief Возвращает указатель на клетку по заданным координатам.
     * @param x Координата по оси X.
     * @param y Координата по оси Y.
     * @return Указатель на клетку.
     */
    Cell* GetCell(int x, int y) const;

    /**
     * @brief Возвращает цвет текущего игрока.
     * @return Цвет текущего игрока.
     */
    Color GetCurrentPlayerColor() const;

    /**
     * @brief Устанавливает цвет текущего игрока.
     * @param color Цвет, который следует установить.
     */
    void SetCurrentPlayerColor(Color color);

    /**
     * @brief Возвращает цвет победившего игрока, если игра завершена.
     * @return Цвет победителя или пустой цвет, если игра еще не завершена.
     */
    Color GetWinner() const;

    /**
     * @brief Очищает шахматную доску, удаляя все фигуры.
     */
    void ClearBoard();

    /**
     * @brief Создает фигуру заданного типа и цвета.
     * @param name Тип фигуры.
     * @param color Цвет фигуры.
     * @param is_first_move Флаг, указывающий, что это первый ход фигуры.
     * @return Указатель на созданную фигуру.
     */
    Piece* CreatePiece(Piece::PieceName name, Color color, bool is_first_move) const;

    /**
     * @brief Устанавливает фигуру на определенную клетку.
     * @param piece Указатель на фигуру.
     * @param row Номер строки клетки.
     * @param col Номер столбца клетки.
     */
    void SetPiece(Piece* piece, int row, int col);

    /**
     * @brief Инициализирует шахматную доску, расставляя фигуры в начальные позиции.
     */
    void InitBoard();

    /**
     * @brief Проверяет, свободна ли диагональ между двумя клетками.
     * @param from_cell Начальная клетка.
     * @param to_cell Конечная клетка.
     * @return true, если диагональ свободна, иначе false.
     */
    bool IsEmptyDiagonal(const Cell* from_cell, const Cell* to_cell) const;

    /**
     * @brief Проверяет, свободен ли горизонтальный путь между двумя клетками.
     * @param from_cell Начальная клетка.
     * @param to_cell Конечная клетка.
     * @return true, если путь свободен, иначе false.
     */
    bool IsEmptyHorizontal(const Cell* from_cell, const Cell* to_cell) const;

    /**
     * @brief Проверяет, свободен ли вертикальный путь между двумя клетками.
     * @param from_cell Начальная клетка.
     * @param to_cell Конечная клетка.
     * @return true, если путь свободен, иначе false.
     */
    bool IsEmptyVertical(const Cell* from_cell, const Cell* to_cell) const;

    /**
     * @brief Проверяет, находится ли клетка под атакой указанного игрока.
     * @param cell Клетка для проверки.
     * @param attacking_player Игрок, атакующий клетку.
     * @return true, если клетка под атакой, иначе false.
     */
    bool IsCellUnderAttack(const Cell* cell, Color attacking_player) const;

    /**
     * @brief Проверяет, находится ли король указанного цвета под шахом.
     * @param king_color Цвет короля.
     * @return true, если король под шахом, иначе false.
     */
    bool IsCheck(Color king_color) const;

    /**
     * @brief Находит клетку, на которой находится король заданного цвета.
     * @param king_color Цвет короля.
     * @return Указатель на клетку с королем.
     */
    Cell* FindKing(Color king_color) const;

    /**
     * @brief Перемещает фигуру с одной клетки на другую.
     * @param from_cell Начальная клетка.
     * @param to_cell Целевая клетка.
     * @param move Тип хода (по умолчанию - обычный ход).
     */
    void MoveFigure(Cell* from_cell, Cell* to_cell, Piece::PieceMove move = Piece::PieceMove::Common);

    /**
     * @brief Устанавливает доступные ходы для фигуры, находящейся на выбранной клетке.
     * @param selected_cell Выбранная клетка с фигурой.
     */
    void SetAvailableMoves(const Cell* selected_cell) const;

    /**
     * @brief Сбрасывает все доступные ходы для фигур.
     */
    void DropAvailableMoves();

    /**
     * @brief Перезапускает игру, очищая и заново инициализируя шахматную доску.
     */
    void Restart();

private:
    /**
     * @brief Устанавливает начальные позиции фигур на доске.
     */
    void AddPieces();

    void AddBishops();  ///< Добавляет слонов на доску.
    void AddKings();    ///< Добавляет королей на доску.
    void AddKnights();  ///< Добавляет коней на доску.
    void AddPawns();    ///< Добавляет пешек на доску.
    void AddQueens();   ///< Добавляет ферзей на доску.
    void AddRooks();    ///< Добавляет ладьи на доску.

    Color current_player_;     ///< Цвет текущего игрока.
    Color winner_;             ///< Цвет победителя (если игра завершена).
    std::array<std::array<Cell*, 8>, 8> cells_; ///< Массив клеток доски.
};
