//
// Created by Lukasz-Lap on 19.05.2020.
//

#pragma once

#include "Connect4AI.h"
#include "SFML/Graphics.hpp"

class Connect4UserInterface {
private:
    Connect4AI &_game;
    sf::RenderWindow &_window;
    sf::Event _event;

    //------
    std::array<std::array<sf::CircleShape, 6>, 7> _coins;

    sf::RectangleShape _board_picture;
    float _board_height;
    float _coin_radius;


    sf::Color _player_color, _ai_color;
    sf::Color _background_color;
    sf::Color _border_color;


    void Start();

    void DisplayGame();

    void End();

    void TakeTurn();

    void UpdateCoinsColors();

    int ColumnSelector(sf::Color player_color);

    int ConvertMousePositionToColumn(sf::Vector2i mouse_position);

public:
    Connect4UserInterface(Connect4AI &game, sf::RenderWindow &window);

    void Run();
};




