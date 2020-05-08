#include <iostream>
#include <SFML/Graphics.hpp>
#include "AlgorithmFunctions.h"
#include "Connect4.h"

//if using Windows Subsystem for Linux - this allows viewing sfml
#define WSL_DISPLAY setenv("DISPLAY", "127.0.0.1:0", true)
#define LOG(x) std::cout << x << std::endl

//test sfml
void SfmlCheck();


int main() {
    Connect4 game;
    game.Run();
    //SfmlCheck();






    return 0;
}


void SfmlCheck() {
    WSL_DISPLAY;
    sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");

    sf::Event event;

    sf::CircleShape circleShape(200);
    circleShape.setFillColor(sf::Color::Blue);

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
        }

        renderWindow.clear();
        renderWindow.draw(circleShape);
        renderWindow.display();
    }
}