#pragma once

#include "piece.h"

/**
 * @brief Класс, представляющий пешку в шахматах.
 *
 * Наследует базовый класс Piece и реализует правила хода пешки.
 */
class Pawn : public Piece
{
public:
    /**
     * @brief Проверяет, может ли пешка переместиться из одной клетки в другую.
     *
     * @param from_cell Клетка, в которой находится пешка.
     * @param to_cell Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     * @return true, если ход возможен, иначе false.
     */
    bool CanMove(const Cell* from_cell, const Cell* to_cell, const Board* board) const override;

    /**
     * @brief Выполняет ход пешкой, включая взятие на проходе и превращение.
     *
     * @param current Текущая клетка пешки.
     * @param target Целевая клетка для перемещения.
     * @param board Указатель на игровую доску.
     */
    void MoveFigure(Cell* current, Cell* target, Board* board) override;

    /**
     * @brief Создает копию пешки.
     *
     * @return Указатель на копию объекта Pawn.
     */
    Piece* GetCopy() const override;

    /**
     * @brief Конструктор, создающий пешку заданного цвета.
     *
     * @param color Цвет пешки.
     */
    Pawn(Color color) : Piece(PieceName::Pawn, color) {}

    /**
     * @brief Конструктор копирования.
     */
    Pawn(const Pawn&) = default;
};
