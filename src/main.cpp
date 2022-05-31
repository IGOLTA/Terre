#include <iostream>
#include <stdexcept>

#include "Game.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main(int argv ,char** argc){
    try {
        Game::launch();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        Game::cleanup();
        return -1;
    }

    Game::cleanup();
    return 0;
}