#include <iostream>
#include <SFML/Graphics.hpp>
#include "Connect4AI.h"
#include "Connect4UserInterface.h"


//if using Windows Subsystem for Linux - this allows viewing sfml
#define WSL_ALLOW_DISPLAY setenv("DISPLAY", "127.0.0.1:0", true)
#define LOG(x) std::cout << x << std::endl

//test sfml
void SfmlCheck();


int main() {
    WSL_ALLOW_DISPLAY;
    Connect4AI game(6);
    sf::RenderWindow window(sf::VideoMode(700, 700), "Connect4 Game");


    Connect4UserInterface ui(game, window);
    ui.Run();



    // game.Run();
    //SfmlCheck();

/*
    WSL_ALLOW_DISPLAY;
    sf::RenderWindow window(sf::VideoMode(850, 850), "Connect 4", sf::Style::Close);
    SfmlManager obj(window, 180, 180);
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                window.close();
        }

        window.clear();
        obj.DrawBoard();
        window.display();
    }

    return 0;
    */
}


void SfmlCheck() {
    WSL_ALLOW_DISPLAY;
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