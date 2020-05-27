#include <iostream>
#include <SFML/Graphics.hpp>
#include "Connect4AI.h"
#include "Connect4UserInterface.h"


//if using Windows Subsystem for Linux - this allows viewing sfml
#define WSL_ALLOW_DISPLAY setenv("DISPLAY", "127.0.0.1:0", true)



int main() {
    WSL_ALLOW_DISPLAY;
    //set default difficulty
    Connect4AI game(6);
    sf::RenderWindow window(sf::VideoMode(700, 700), "Connect4 Game");
    window.setVerticalSyncEnabled(true);
    Connect4UserInterface ui(game, window);
    ui.Run();
}


