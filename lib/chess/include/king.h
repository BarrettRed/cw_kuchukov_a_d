#pragma once

#include "piece.h"

/**
 * @brief Класс, представляющий короля в шахматах.
 *
 * Наследует базовый класс Piece и реализует правила хода короля.
 */
class King : public Piece
{
public:
    /**
     * @brief Проверяет, может ли король переместиться из одной клетки в другую.
     *
     * @param from_cell Клетка, в которой находится король.
     * @param to_cell Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     * @return true, если ход возможен, иначе false.
     */
    bool CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const override;

    /**
     * @brief Создает копию короля.
     *
     * @return Указатель на копию объекта King.
     */
    Piece* GetCopy() const override;

    /**
     * @brief Выполняет перемещение короля на новую клетку.
     *
     * @param current Текущая клетка, в которой находится король.
     * @param target Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     */
    void MoveFigure(Cell* current, Cell* target, Board* board) override;

    /**
     * @brief Конструктор, создающий короля заданного цвета.
     *
     * @param color Цвет короля.
     */
    King(Color color) : Piece(PieceName::King, color) {};

    /**
     * @brief Конструктор копирования.
     */
    King(const King&) = default;
};
