#pragma once

#include "piece.h"

/**
 * @brief Класс, представляющий коня в шахматах.
 *
 * Наследует базовый класс Piece и реализует правила хода коня.
 */
class Knight : public Piece
{
public:
    /**
     * @brief Проверяет, может ли конь переместиться из одной клетки в другую.
     *
     * @param from_cell Клетка, в которой находится конь.
     * @param to_cell Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     * @return true, если ход возможен, иначе false.
     */
    bool CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const override;

    /**
     * @brief Создает копию коня.
     *
     * @return Указатель на копию объекта Knight.
     */
    Piece* GetCopy() const override;

    /**
     * @brief Конструктор, создающий коня заданного цвета.
     *
     * @param color Цвет коня.
     */
    Knight(Color color) : Piece(PieceName::Knight, color) {};

    /**
     * @brief Конструктор копирования.
     */
    Knight(const Knight&) = default;
};
