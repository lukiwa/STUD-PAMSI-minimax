#include <iostream>
#include <SFML/Graphics.hpp>

//if using Windows Subsystem for Linux - this allows viewing sfml
#define WSL_DISPLAY setenv("DISPLAY", "127.0.0.1:0", true)

//test
void SfmlCheck();

int main() {
    WSL_DISPLAY;
    SfmlCheck();

}


void SfmlCheck() {
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