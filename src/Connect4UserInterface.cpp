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

}

/**
 * @brief Game loop
 */
void Connect4UserInterface::Run() {
    Start();


    Start();
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::EventType::Closed) { _window.close(); }
            TakeTurn();
            UpdateCoinsColors();

            DisplayGame();

            if (_game.HaveWinner()) {
                std::cout << "KONIEC" << std::endl;
                while (1) {

                }
            }
            if (_game.IsTie()) { return; }
        }

    }

    End();
}

/**
 * @brief Starting screen
 */
void Connect4UserInterface::Start() {
    DisplayGame();
}

/**
 * @brief End screen
 */
void Connect4UserInterface::End() {

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


    _window.display();
}

/**
 * @brief Allow user to drop coin in selected column, or performs finding best move by AI
 */
void Connect4UserInterface::TakeTurn() {
    if (_game.GetCurrentPlayer() == BoardPositionState::PLAYER) {
        int column = 0;
        std::cin >> column;
        _game.DropCoin(column, BoardPositionState::PLAYER);

        _game.ChangeCurrentPlayer();
        return;
    }

    if (_game.GetCurrentPlayer() == BoardPositionState::AI) {
        auto column = _game.FindBestMove();
        std::cout << "Column" << column << std::endl;
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


