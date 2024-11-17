#pragma once

#include <SFML/Graphics.hpp>

#include "board.h"
#include "timer.h"

/**
 * @brief Класс Game управляет игровым процессом, отрисовкой элементов интерфейса и взаимодействием с пользователем.
 */
class Game
{
public:
    /**
     * @brief Конструктор игры.
     *
     * Инициализирует все необходимые компоненты, такие как доска, таймеры, текстуры и шрифты.
     */
    Game();

    /**
     * @brief Основной игровой цикл.
     *
     * Обрабатывает события, обновляет состояние игры и выполняет отрисовку.
     */
    void MainLoop();

private:
    /**
     * @brief Отрисовка шахматной доски.
     */
    void DrawBoard();

    /**
     * @brief Отрисовка доступного хода.
     *
     * @param i Строка клетки.
     * @param j Столбец клетки.
     */
    void DrawAvailableMove(int i, int j);

    /**
     * @brief Отрисовка кнопок интерфейса (например, "Сохранить", "Загрузить", "Рестарт").
     */
    void DrawButtons();

    /**
     * @brief Отрисовка одной клетки доски.
     *
     * @param i Строка клетки.
     * @param j Столбец клетки.
     */
    void DrawCell(int i, int j);

    /**
     * @brief Отрисовка фигуры на указанной клетке.
     *
     * @param piece Указатель на фигуру.
     * @param i Строка клетки.
     * @param j Столбец клетки.
     */
    void DrawPiece(const Piece* piece, int i, int j);

    /**
     * @brief Отрисовка предупреждающего прямоугольника (например, при шахе).
     *
     * @param i Строка клетки.
     * @param j Столбец клетки.
     */
    void DrawWarningRectangle(int i, int j);

    /**
     * @brief Отрисовка таймеров игроков.
     */
    void DrawTimers();

    /**
     * @brief Отображение победителя игры.
     *
     * @param color Цвет победившего игрока.
     */
    void DrawWinner(Color color);

    /**
     * @brief Обработка кликов мыши.
     *
     * @param mouseX Координата X мыши.
     * @param mouseY Координата Y мыши.
     */
    void HandleMouseClick(int mouseX, int mouseY);

    /**
     * @brief Сохранение текущего состояния игры в файл.
     */
    void SaveGame();

    /**
     * @brief Загрузка состояния игры из файла.
     */
    void LoadGame();

    /**
     * @brief Перезапуск игры.
     *
     * Сбрасывает состояние доски, таймеров и других параметров.
     */
    void Restart();

    Board board_;                      /**< Объект шахматной доски. */
    Cell* selected_cell_;              /**< Указатель на текущую выбранную клетку. */
    Timer white_player_timer_;         /**< Таймер для белого игрока. */
    Timer black_player_timer_;         /**< Таймер для черного игрока. */
    sf::RenderWindow window_;          /**< Окно приложения SFML. */
    sf::CircleShape available_circle_; /**< Графический элемент для отображения доступных ходов. */
    sf::Texture textures_[2][6];       /**< Массив текстур для фигур. */
    sf::Sprite sprites_[2][6];         /**< Массив спрайтов для фигур. */
    sf::Sprite buttons_;               /**< Спрайт кнопок интерфейса. */
    sf::RectangleShape drawable_cells_[8][8]; /**< Массив графических элементов для клеток доски. */
    sf::Font font_;                    /**< Шрифт для текста в игре. */
};
