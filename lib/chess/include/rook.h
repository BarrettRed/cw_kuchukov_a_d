#pragma once

#include "piece.h"

/**
 * @brief Класс, представляющий ладью в шахматах.
 *
 * Наследует базовый класс Piece и реализует правила хода ладьи.
 */
class Rook : public Piece
{
public:
    /**
     * @brief Проверяет, может ли ладья переместиться из одной клетки в другую.
     *
     * Ладья может ходить только по прямой линии горизонтально или вертикально.
     *
     * @param from_cell Клетка, в которой находится ладья.
     * @param to_cell Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     * @return true, если ход возможен, иначе false.
     */
    bool CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const override;

    /**
     * @brief Создает копию ладьи.
     *
     * @return Указатель на копию объекта Rook.
     */
    Piece* GetCopy() const override;

    /**
     * @brief Конструктор, создающий ладью заданного цвета.
     *
     * @param color Цвет ладьи.
     */
    Rook(Color color) : Piece(PieceName::Rook, color) {}

    /**
     * @brief Конструктор копирования.
     */
    Rook(const Rook&) = default;
};
