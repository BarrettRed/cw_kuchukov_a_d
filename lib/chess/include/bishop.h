#pragma once

#include "piece.h"

/**
 * @brief Класс, представляющий слона в шахматах.
 *
 * Наследует базовый класс Piece и реализует правила хода слона.
 */
class Bishop : public Piece
{
public:
    /**
     * @brief Проверяет, может ли слон переместиться из одной клетки в другую.
     *
     * @param from_cell Клетка, в которой находится слон.
     * @param to_cell Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     * @return true, если ход возможен, иначе false.
     */
    bool CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const override;

    /**
     * @brief Создает копию слона.
     *
     * @return Указатель на копию объекта Bishop.
     */
    Piece* GetCopy() const override;

    /**
     * @brief Конструктор, создающий слона заданного цвета.
     *
     * @param color Цвет слона.
     */
    Bishop(Color color) : Piece(PieceName::Bishop, color) {};

    /**
     * @brief Конструктор копирования.
     */
    Bishop(const Bishop&) = default;
};
