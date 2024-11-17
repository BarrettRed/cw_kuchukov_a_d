#pragma once

#include "piece.h"

/**
 * @brief Класс, представляющий ферзя в шахматах.
 *
 * Наследует базовый класс Piece и реализует правила хода ферзя.
 */
class Queen : public Piece
{
public:
    /**
     * @brief Проверяет, может ли ферзь переместиться из одной клетки в другую.
     *
     * @param from_cell Клетка, в которой находится ферзь.
     * @param to_cell Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     * @return true, если ход возможен, иначе false.
     */
    bool CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const override;

    /**
     * @brief Создает копию ферзя.
     *
     * @return Указатель на копию объекта Queen.
     */
    Piece* GetCopy() const override;

    /**
     * @brief Конструктор, создающий ферзя заданного цвета.
     *
     * @param color Цвет ферзя.
     */
    Queen(Color color) : Piece(PieceName::Queen, color) {}

    /**
     * @brief Конструктор копирования.
     */
    Queen(const Queen&) = default;
};
