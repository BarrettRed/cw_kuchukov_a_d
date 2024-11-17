#include <fstream>
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <tinyfiledialogs/tinyfiledialogs.h>

#include "game.h"

Game::Game() : board_(),
               selected_cell_(nullptr),
               white_player_timer_(600, font_, sf::Vector2f(700, 600)),
               black_player_timer_(600, font_, sf::Vector2f(700, 0)),
               window_(sf::VideoMode(835, 640), "Chess", sf::Style::Titlebar | sf::Style::Close),
               available_circle_(15),
               font_()
{
    sf::Image icon;
    icon.loadFromFile("res/rook_black.png");
    window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window_.setPosition(sf::Vector2i(100, 100));

    board_.InitBoard();

    available_circle_.setFillColor(sf::Color(0, 255, 0, 100));

    // Загрузка текстур для черных фигур
    textures_[0][0].loadFromFile("res/bishop_black.png");
    textures_[0][1].loadFromFile("res/king_black.png");
    textures_[0][2].loadFromFile("res/knight_black.png");
    textures_[0][3].loadFromFile("res/pawn_black.png");
    textures_[0][4].loadFromFile("res/queen_black.png");
    textures_[0][5].loadFromFile("res/rook_black.png");

    // Загрузка текстур для белых фигур
    textures_[1][0].loadFromFile("res/bishop_white.png");
    textures_[1][1].loadFromFile("res/king_white.png");
    textures_[1][2].loadFromFile("res/knight_white.png");
    textures_[1][3].loadFromFile("res/pawn_white.png");
    textures_[1][4].loadFromFile("res/queen_white.png");
    textures_[1][5].loadFromFile("res/rook_white.png");

    // Инициализация спрайтов на основе загруженных текстур
    float k_scale = 80.0f / 141.0f;
    for (int color = 0; color < 2; color++) {
        for (int piece = 0; piece < 6; piece++) {
            sprites_[color][piece].setTexture(textures_[color][piece]);
            sprites_[color][piece].setScale(k_scale, k_scale);  // Масштабируем до 80x80
        }
    }

    sf::Texture tex_buttons;
    tex_buttons.loadFromFile("res/buttons.png");
    buttons_.setTexture(tex_buttons);
    buttons_.setPosition(660, 60);
    buttons_.setScale(0.65, 0.65);

    // Инициализация клеток со светло-коричневыми тонами
    sf::Color lightBrown(210, 180, 140);   // #D2B48C (Tan)
    sf::Color darkBrown(139, 69, 19);      // #8B4513 (SaddleBrown)

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            drawable_cells_[i][j].setSize(sf::Vector2f(80, 80));  // Устанавливаем размер клетки
            drawable_cells_[i][j].setPosition(80 * i, 80 * j);    // Устанавливаем позицию клетки
            drawable_cells_[i][j].setFillColor((i + j) % 2 == 0 ? lightBrown : darkBrown);  // Устанаавливаем цвет клетки
        }
    }

    font_.loadFromFile("res/Roboto-Regular.ttf");

    MainLoop();  // Запуск основного цикла игры
}


void Game::DrawBoard()
{
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            this->DrawCell(i, j);
            this->DrawPiece(board_.GetCell(i, j)->GetPiece(), i, j);
            if (selected_cell_)
                DrawAvailableMove(i, j);
        }
    }
    
    sf::RectangleShape frame(sf::Vector2f(640, 640));
    frame.setPosition(0, 0);
    frame.setOutlineColor(sf::Color(31, 27, 10));
    frame.setOutlineThickness(3);
    frame.setFillColor(sf::Color::Transparent);
    window_.draw(frame);

    if (board_.GetWinner() == Color::None && board_.IsCheck(board_.GetCurrentPlayerColor())) {
        Cell* king_cell = board_.FindKing(board_.GetCurrentPlayerColor());
        DrawWarningRectangle(king_cell->x_, king_cell->y_);
    }

    DrawTimers();
    DrawButtons();

    if (board_.GetWinner() != Color::None)
        DrawWinner(board_.GetWinner());
}

void Game::DrawAvailableMove(int i, int j) {
    if (board_.GetCell(i, j)->IsAvailable()) {
        available_circle_.setPosition(80 * i + 25, 80 * j + 25); // Смещение для центра круга
        window_.draw(available_circle_);
    }
}

void Game::DrawButtons() {
    window_.draw(buttons_);
}

void Game::DrawCell(int i, int j) {
    window_.draw(drawable_cells_[i][j]);  
}


void Game::DrawPiece(const Piece* piece, int i, int j) {
    if (piece) {
        Color color = piece->GetColor();
        int piece_name = static_cast<int>(piece->GetPieceName());  
        sf::Sprite& sprite = sprites_[color == Color::Black ? 0 : 1][piece_name];
        sprite.setPosition(80 * i, 80 * j);
        window_.draw(sprite);
    }
}

void Game::DrawTimers() 
{
    white_player_timer_.Update();
    white_player_timer_.Draw(window_);
    black_player_timer_.Update();
    black_player_timer_.Draw(window_);
}

void Game::DrawWinner(Color color)
{
    sf::Texture tex;
    if (color == Color::White)
        tex.loadFromFile("res/white_won.png");
    else
        tex.loadFromFile("res/black_won.png");
    
    sf::Sprite sprite(tex);
    sprite.setPosition(265, 70);
    window_.draw(sprite);
}

void Game::DrawWarningRectangle(int i, int j)
{
    sf::RectangleShape warning_rect(sf::Vector2f(80, 80));
    warning_rect.setPosition(80 * i, 80 * j);
    warning_rect.setOutlineColor(sf::Color::Red);
    warning_rect.setOutlineThickness(5);
    warning_rect.setFillColor(sf::Color::Transparent);
    window_.draw(warning_rect);
}


void Game::HandleMouseClick(int mouseX, int mouseY) {    
    if (board_.GetWinner() != Color::None)
        Restart();
    if (mouseX <= 640 && mouseY <= 640) {
        int i = mouseX / 80;
        int j = mouseY / 80;
        Cell* cell = board_.GetCell(i, j);
        if (selected_cell_ && cell->IsAvailable()) {
            if (board_.GetCurrentPlayerColor() == Color::White) {
                white_player_timer_.Stop();
                black_player_timer_.Start();
            }
            else {
                black_player_timer_.Stop();
                white_player_timer_.Start();
            }
            board_.MoveFigure(selected_cell_, cell);
            board_.DropAvailableMoves();
        }
        else if (!cell->IsEmpty() && cell->GetPiece()->GetColor() == board_.GetCurrentPlayerColor()) {
            selected_cell_ = cell;
            board_.SetAvailableMoves(selected_cell_);
        }
    }
    
    static const int R(75);
    static const sf::Vector2i new_game_center  { 740, 150 };
    static const sf::Vector2i save_game_center { 740, 320 };
    static const sf::Vector2i load_game_center { 740, 500 };
    int diff_x = abs(mouseX - 740);
    if (diff_x < R) {
        if (pow(diff_x, 2) + pow((mouseY - new_game_center.y), 2) < R * R)
            Restart();
        if (pow(diff_x, 2) + pow((mouseY - save_game_center.y), 2) < R * R)
            SaveGame();
        if (pow(diff_x, 2) + pow((mouseY - load_game_center.y), 2) < R * R)
            LoadGame();
    }
}


void Game::MainLoop()
{
    while (window_.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window_.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window_.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    HandleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        window_.clear(sf::Color(193, 180, 148));
        this->DrawBoard();
        window_.display();
    }
}

void Game::SaveGame() {
    if (board_.GetCurrentPlayerColor() == Color::White) 
        white_player_timer_.Stop();
    else 
        black_player_timer_.Stop();

    std::string save_dir = std::filesystem::current_path().string() + "/saves";
    std::filesystem::create_directories(save_dir);
    std::string default_filename = save_dir + "/chess_save.json";

    const char* filter_patterns[1] = { "*.json" };
    const char* path = tinyfd_saveFileDialog(
        "Save Game",                // Заголовок диалога
        default_filename.c_str(),    // Имя файла по умолчанию
        1,                           // Количество фильтров
        filter_patterns,             // Массив фильтров
        "JSON Files"                 // Описание фильтров
    );


    if (path) {
        nlohmann::json save_json;

        save_json["current_player_color"] = static_cast<int>(board_.GetCurrentPlayerColor());

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                const Piece* piece = board_.GetCell(i, j)->GetPiece();
                if (piece)
                    save_json["board"][i][j] = { static_cast<int>(piece->GetPieceName()),
                                                 static_cast<int>(piece->GetColor()),
                                                 piece->IsFirstMove() };
                else
                    save_json["board"][i][j] = nullptr;
            }
        }

        save_json["timers"]["white"] = white_player_timer_.GetRemainingTime();
        save_json["timers"]["black"] = black_player_timer_.GetRemainingTime();

        std::ofstream file(path);
        file << save_json.dump(4);  
        std::cout << "Game saved to " << path << std::endl;
    }

    if (board_.GetCurrentPlayerColor() == Color::White) 
        white_player_timer_.Start();
    else 
        black_player_timer_.Start();
}

void Game::LoadGame() {
    const char* filter_patterns[1] = { "*.json" };
    const char* path = tinyfd_openFileDialog("Load Game", "", 1, filter_patterns, "JSON Files", 0);
    
    if (!path) {
        return;  
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    nlohmann::json game_data;
    try {
        file >> game_data; 
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return;  
    }

    
    int current_color = game_data["current_player_color"];
    board_.SetCurrentPlayerColor(static_cast<Color>(current_color));
    
    float white_timer_time = game_data["timers"]["white"];
    white_player_timer_.SetRemainingTime(white_timer_time);
    float black_timer_time = game_data["timers"]["black"];
    black_player_timer_.SetRemainingTime(black_timer_time);

    board_.ClearBoard();
    for (int i = 0; i < 8; ++i) 
        for (int j = 0; j < 8; ++j) {
            if (!game_data["board"][i][j].is_null()) {
                Piece::PieceName name = static_cast<Piece::PieceName>(game_data["board"][i][j][0]);
                Color color = static_cast<Color>(game_data["board"][i][j][1]);
                bool is_first_move = game_data["board"][i][j][2];
                board_.SetPiece(board_.CreatePiece(name, color, is_first_move), j, i);
            }
        }

    if (board_.GetCurrentPlayerColor() == Color::White) {
        white_player_timer_.Start();
        black_player_timer_.Stop();
    }
    else {
        black_player_timer_.Start();
        white_player_timer_.Stop();
    }
}

void Game::Restart() 
{
    board_.Restart();
    white_player_timer_.Reset();
    black_player_timer_.Reset();
}