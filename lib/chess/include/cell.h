#pragma once

#include "colors.h"
#include "piece.h"

/**
 * @brief Класс Cell представляет клетку на шахматной доске.
 * 
 * Класс управляет состоянием клетки, включая фигуру, цвет клетки и доступность для хода.
 */
class Cell {
public:
    const int x_;  ///< Координата столбца (X) клетки.
    const int y_;  ///< Координата строки (Y) клетки.

    /**
     * @brief Конструктор, инициализирующий клетку заданными параметрами.
     * @param x Координата столбца.
     * @param y Координата строки.
     * @param color Цвет клетки.
     * @param piece Указатель на фигуру, находящуюся на клетке (может быть nullptr).
     */
    Cell(int x, int y, Color color, Piece* piece) : x_(x), y_(y), color_(color), piece_(piece), is_available_(false) {};

    /**
     * @brief Конструктор копирования для создания копии клетки.
     * @param cell Другая клетка для копирования.
     */
    Cell(const Cell& cell) : x_(cell.x_), y_(cell.y_),
                             color_(cell.color_),
                             piece_(cell.piece_ ? cell.piece_->GetCopy() : nullptr),
                             is_available_(cell.is_available_) {};

    /**
     * @brief Деструктор, удаляющий фигуру на клетке, если она есть.
     */
    ~Cell();

    /**
     * @brief Возвращает указатель на фигуру, находящуюся на клетке.
     * @return Указатель на фигуру или nullptr, если клетка пуста.
     */
    Piece* GetPiece() const;

    /**
     * @brief Возвращает цвет клетки.
     * @return Цвет клетки.
     */
    Color GetColor() const;

    /**
     * @brief Проверяет, является ли фигура на целевой клетке вражеской.
     * @param target Указатель на целевую клетку для проверки.
     * @return true, если фигура на целевой клетке вражеская, иначе false.
     */
    bool IsEnemy(const Cell* target) const;

    /**
     * @brief Проверяет, пуста ли клетка.
     * @return true, если клетка пуста, иначе false.
     */
    bool IsEmpty() const;

    /**
     * @brief Удаляет фигуру с клетки.
     */
    void DeletePiece();

    /**
     * @brief Устанавливает фигуру на клетку.
     * @param piece Указатель на фигуру.
     */
    void SetPiece(Piece* piece);

    /**
     * @brief Проверяет, доступна ли клетка для хода.
     * @return true, если клетка доступна, иначе false.
     */
    bool IsAvailable() const;

    /**
     * @brief Устанавливает доступность клетки для хода.
     * @param available Доступность клетки.
     */
    void SetAvailable(bool available);

private:
    Color color_;           ///< Цвет клетки.
    Piece* piece_;          ///< Указатель на фигуру на клетке (может быть nullptr).
    bool is_available_;     ///< Флаг, указывающий, доступна ли клетка для хода.
};
