#pragma once
#include "colors.h"

class Board;
class Cell;

/**
 * @brief Абстрактный базовый класс для шахматных фигур.
 * 
 * Определяет интерфейс для всех фигур и общие атрибуты,
 * такие как имя фигуры, цвет и информация о первом ходе.
 */
class Piece {
public:
    /**
     * @brief Названия типов фигур.
     */
    enum class PieceName { Bishop, King, Knight, Pawn, Queen, Rook };

    /**
     * @brief Типы возможных ходов фигуры.
     */
    enum class PieceMove { Castling, Common };

    /**
     * @brief Проверяет возможность хода фигуры с одной клетки на другую.
     * @param from_cell Указатель на клетку, с которой осуществляется ход.
     * @param to_cell Указатель на клетку, на которую осуществляется ход.
     * @param board Указатель на игровую доску.
     * @return true, если ход возможен, иначе false.
     */
    virtual bool CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const = 0;

    /**
     * @brief Возвращает копию текущей фигуры.
     * @return Указатель на новую фигуру.
     */
    virtual Piece* GetCopy() const = 0;

    /**
     * @brief Возвращает тип фигуры.
     * @return Имя фигуры из перечисления PieceName.
     */
    PieceName GetPieceName() const;

    /**
     * @brief Возвращает цвет фигуры.
     * @return Цвет фигуры (белый или черный).
     */
    Color GetColor() const;

    /**
     * @brief Проверяет, является ли текущий ход для фигуры первым.
     * @return true, если ход первый, иначе false.
     */
    bool IsFirstMove() const;

    /**
     * @brief Устанавливает статус первого хода для фигуры.
     * @param is_first_move true, если ход первый, иначе false.
     */
    void SetFirstMove(bool is_first_move);

    /**
     * @brief Выполняет перемещение фигуры с одной клетки на другую.
     * 
     * @param current Указатель на текущую клетку фигуры.
     * @param target Указатель на целевую клетку для перемещения.
     * @param board Указатель на игровую доску.
     */
    virtual void MoveFigure(Cell* current, Cell* target, Board* board);

    Piece() = delete;
    
    /**
     * @brief Конструктор, инициализирующий фигуру с заданным типом и цветом.
     * @param name Тип фигуры.
     * @param color Цвет фигуры.
     */
    Piece(PieceName name, Color color) : name_(name), color_(color), is_first_move_(true) {}

    /**
     * @brief Конструктор копирования по умолчанию.
     * @param piece Существующая фигура для копирования.
     */
    Piece(const Piece& piece) = default;

    /**
     * @brief Деструктор по умолчанию.
     */
    ~Piece() = default;

private:
    PieceName name_;        ///< Тип фигуры.
    Color color_;           ///< Цвет фигуры.
    bool is_first_move_;    ///< Флаг, показывающий, что это первый ход фигуры.
};

