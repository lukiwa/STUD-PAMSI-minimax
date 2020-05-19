//
// Created by Lukasz-Lap on 19.05.2020.
//

#include "SfmlManager.h"


void SfmlManager::SetPlayerColor(BoardPositionState player, sf::Color color) {

    switch (player) {
        case BoardPositionState::PLAYER :
            _player_color = color;
            break;
        case BoardPositionState::AI:
            _ai_color = color;
            break;
        default:
            std::cout << "unknown player" << std::endl;
    }
}

SfmlManager::SfmlManager(int width, int height) :
        _width(width),
        _height(height) {

    //_coin_radius = window.getSize().x / width / 3;
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

   // _board_picture.setSize(sf::Vector2f(window.getSize().x, window.getSize().y - 3 * _coin_radius));
    _board_picture.setFillColor(sf::Color(71, 133, 228));
    _board_picture.setPosition(0, 3 * _coin_radius);

}

void SfmlManager::DrawBoard() {
    //_window.draw(_board_picture);

}


