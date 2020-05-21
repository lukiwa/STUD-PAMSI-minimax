//
// Created by Lukasz-Lap on 19.05.2020.
//

#include "Connect4UserInterface.h"

Connect4UserInterface::Connect4UserInterface(Connect4AI &game, sf::RenderWindow &window) :
        _game(game),
        _window(window) {

    std::cout << window.getSize().x << window.getSize().y << std::endl;
    _player_color = sf::Color::Red;
    _ai_color = sf::Color::Yellow;

    _coin_radius = window.getSize().x / 3 / 7;
    _background_color = sf::Color(170, 196, 239);
    _border_color = sf::Color(2, 37, 94);

    sf::CircleShape coin(_coin_radius);
    coin.setFillColor(_background_color);
    coin.setOrigin(_coin_radius, _coin_radius);
    coin.setOutlineThickness(5);
    coin.setOutlineColor(_border_color);

    for (auto &i: _coins) {
        std::fill(i.begin(), i.end(), coin);
    }

    _board_height = window.getSize().y - 3 * _coin_radius;
    _board_picture.setSize(sf::Vector2f(window.getSize().x, _board_height));
    _board_picture.setFillColor(sf::Color::Blue);
    _board_picture.setPosition(0, 3 * _coin_radius);

    _to_drop_coin.setRadius(_coin_radius);
    _to_drop_coin.setOrigin(_coin_radius, _coin_radius);

}

/**
 * @brief Game loop
 */
void Connect4UserInterface::Run() {


    Start();

    while (_window.isOpen()) {

        TakeTurn();
        UpdateCoinsColors();
        DisplayGame();


        if (_game.HaveWinner()) {

            auto winner = _game.GetWinner();
            if (winner == BoardPositionState::PLAYER) {
                _state = TerminalGameState::PLAYER_WINS;
            }
            if (winner == BoardPositionState::AI) {
                _state = TerminalGameState::AI_WINS;
            }
            break;
        }
        if (_game.IsTie()) {
            _state = TerminalGameState::TIE;
            break;
        }
    }

    End();
}

/**
 * @brief Starting screen
 */
void Connect4UserInterface::Start() {

    sf::Font font;
    font.loadFromFile("../SFML-2.5.1/fonts/CaviarDreams.ttf");

    sf::Text title, game_mode_1, game_mode_2;
    title.setString("CONNECT FOUR");
    game_mode_1.setString("1. Player vs Player");
    game_mode_2.setString("2. Player vs AI");
    sf::Color texts_color(sf::Color::Black);

    _window.clear(_background_color);

    SetText(title,
            font,
            texts_color,
            50,
            sf::Vector2i(_window.getSize().x / 2, _window.getSize().y / 3));
    _window.draw(title);


    SetText(game_mode_1,
            font,
            texts_color,
            35,
            sf::Vector2i(_window.getSize().x / 2, title.getPosition().y + 75));
    _window.draw(game_mode_1);

    SetText(game_mode_2,
            font,
            texts_color,
            35,
            sf::Vector2i(_window.getSize().x / 2, title.getPosition().y + 150));
    _window.draw(game_mode_2);
    _window.display();

    //loop until player selects gamemode
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _window.close();
                exit(1);
            }
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Num1) {
                _player_vs_player = true;
                return;
            }
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Num2) {
                _player_vs_player = false;
                DifficultySelector();
                return;
            }
        }
    }

}

/**
 * @brief Allow player to set difficulty
 */
void Connect4UserInterface::DifficultySelector() {
    sf::Font font;
    font.loadFromFile("../SFML-2.5.1/fonts/CaviarDreams.ttf");

    sf::Text title, difficulty_easy, difficulty_moderate, difficulty_hard;
    title.setString("Select difficulty");
    difficulty_easy.setString("1. Easy (depth = 2)");
    difficulty_moderate.setString("2. Moderate (depth = 4)");
    difficulty_hard.setString("3. Hard (depth = 6)");
    sf::Color texts_color(sf::Color::Black);

    _window.clear(_background_color);

    SetText(title,
            font,
            texts_color,
            50,
            sf::Vector2i(_window.getSize().x / 2, _window.getSize().y / 4));
    _window.draw(title);


    SetText(difficulty_easy,
            font,
            texts_color,
            35,
            sf::Vector2i(_window.getSize().x / 2, title.getPosition().y + 75));
    _window.draw(difficulty_easy);

    SetText(difficulty_moderate,
            font,
            texts_color,
            35,
            sf::Vector2i(_window.getSize().x / 2, title.getPosition().y + 150));
    _window.draw(difficulty_moderate);

    SetText(difficulty_hard,
            font,
            texts_color,
            35,
            sf::Vector2i(_window.getSize().x / 2, title.getPosition().y + 225));
    _window.draw(difficulty_hard);
    _window.display();


    //loop until player selects difficulty
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _window.close();
                exit(1);
            }
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Num1) {
                _game.SetMaxDepth(2);
                return;
            }
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Num2) {
                _game.SetMaxDepth(4);
                return;
            }
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Num3) {
                _game.SetMaxDepth(6);
                return;
            }
        }
    }
}


/**
 * @brief Display board
 */
void Connect4UserInterface::DisplayGame() {
    _window.clear(_background_color);

    _window.draw(_board_picture);
    float current_x = _board_picture.getPosition().x + 1.5 * _coin_radius;
    float current_y = _board_picture.getPosition().y + 1.5 * _coin_radius;

    for (int i = 0; i < _game.GetRowNumber(); ++i) {
        _coins[0][i].setPosition(current_x, current_y);
        _window.draw(_coins[0][i]);
        for (int j = 1; j < _game.GetColumnNumber(); ++j) {
            current_x += 3 * _coin_radius;
            _coins[j][i].setPosition(current_x, current_y);
            _window.draw(_coins[j][i]);
        }
        current_y += 3 * _coin_radius;
        current_x = _board_picture.getPosition().x + 1.5 * _coin_radius;
    }

    _window.draw(_to_drop_coin);
    _window.display();
}

/**
 * @brief Allow user to drop coin in selected column, or performs finding best move by AI
 */
void Connect4UserInterface::TakeTurn() {
    if (_game.GetCurrentPlayer() == BoardPositionState::PLAYER) {
        auto column = ColumnSelector(_player_color);
        _game.DropCoin(column, BoardPositionState::PLAYER);
        _game.ChangeCurrentPlayer();
        return;
    }


    if (_game.GetCurrentPlayer() == BoardPositionState::AI) {
        int column;
        if (_player_vs_player) {
            column = ColumnSelector(_ai_color);
        } else {
            column = _game.FindBestMove();
        }

        _game.DropCoin(column, BoardPositionState::AI);
        _game.ChangeCurrentPlayer();

        return;
    }
}

/**
 * @brief Update colors of the board based on board status
 */
void Connect4UserInterface::UpdateCoinsColors() {
    auto last_move = _game.GetLastMove();

    if (last_move.state == BoardPositionState::AI) {
        _coins[last_move.column][last_move.row].setFillColor(_ai_color);
    }
    if (last_move.state == BoardPositionState::PLAYER) {
        _coins[last_move.column][last_move.row].setFillColor(_player_color);
    }
}

/**
 * @brief Converts mouse postion to given column
 * @note Need to check whether column number is in range further
 * @param mouse_position position of the mouse in the window
 * @return selected column
 */
int Connect4UserInterface::ConvertMousePositionToColumn(const sf::Vector2i &mouse_position) {

    float column_length = _window.getSize().x / _game.GetColumnNumber();

    return mouse_position.x / column_length;
}

/**
 * @brief Allow to pick column by mouse hover and click
 * @param player_color which color is to be displayed at the top of the board
 * @return picked column
 */
int Connect4UserInterface::ColumnSelector(const sf::Color &player_color) {

    _to_drop_coin.setFillColor(player_color);


    while (true) {
        //make coin follow the mouse
        const sf::Vector2i mouse_pos{sf::Mouse::getPosition(_window)};
        const sf::Vector2f mouse_coord{_window.mapPixelToCoords(mouse_pos)};
        _to_drop_coin.setPosition(sf::Vector2f(mouse_coord.x, 1.5 * _coin_radius));


        DisplayGame();


        while (_window.pollEvent(_event)) {
            //if user clicked - drop the coin
            if (_event.type == sf::Event::MouseButtonPressed) {
                //converts mouse postion to column - allow to pick only possible columns
                return ConvertMousePositionToColumn(mouse_pos) % (_game.GetColumnNumber() + 1);
            }
            //also checks if user wants to end the game
            if (_event.type == sf::Event::EventType::Closed) {
                _window.close();
                exit(1);
            }
        }


    }

}

/**
 * @brief Draw ending text of the game
 */
void Connect4UserInterface::DrawEndText() {
    sf::Text winner_text;

    if (_state == TerminalGameState::TIE) {
        winner_text.setString("It's a Tie!");
    }
    if (_state == TerminalGameState::PLAYER_WINS) {
        winner_text.setString("Player wins!");
    }
    if (_state == TerminalGameState::PLAYER2_WINS) {
        winner_text.setString("Player 2 wins!");
    }
    if (_state == TerminalGameState::AI_WINS) {
        winner_text.setString("AI wins!");
    }

    sf::Font font;
    font.loadFromFile("../SFML-2.5.1/fonts/CaviarDreams.ttf");
    SetText(winner_text,
            font, sf::Color::Black,
            70,
            sf::Vector2i(_window.getSize().x / 2, _window.getSize().y / 2));

    _window.draw(winner_text);
}


/**
 * @brief End screen loop
 */
void Connect4UserInterface::End() {
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::MouseButtonPressed) {
                _window.close();
                exit(1);
            }
            if (_event.type == sf::Event::Closed) {
                _window.close();
                exit(1);
            }

        }

        DrawEndText();
        _window.display();
    }

}

/**
 * @brief Set text on the screen
 * @param text Text to be displayed
 * @param font selected font
 * @param color selected color
 * @param font_size font size
 * @param position position on the screen
 */
void Connect4UserInterface::SetText(sf::Text &text, const sf::Font &font, const sf::Color &color, int font_size,
                                    const sf::Vector2i &position) const {

    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(font_size);
    sf::FloatRect f = text.getLocalBounds();
    text.setOrigin(f.width / 2, 0);
    text.setPosition(position.x, position.y);
}





