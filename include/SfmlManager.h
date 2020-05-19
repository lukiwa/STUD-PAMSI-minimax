//
// Created by Lukasz-Lap on 19.05.2020.
//



#pragma once

#include "SFML/Graphics.hpp"
#include "Connect4AI.h"

class SfmlManager {
private:
    std::array<std::array<sf::CircleShape, 6>, 7> _coins;

    sf::RectangleShape _board_picture;
    int _width, _height;

    sf::Color _player_color, _ai_color;
    sf::Color _background_color;
    sf::Color _border_color;

    float _coin_radius;


public:
    SfmlManager(int width, int height);

    void SetPlayerColor(BoardPositionState player, sf::Color color);
    void DrawBoard();
};




