//
// Created by louis on 17/05/22.
//

#ifndef TERRE_GAME_H
#define TERRE_GAME_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "resources/shader/ShaderLoader.h"
#include "resources/Mesh.h"
#include "ui/custom/MainMenu.h"
#include "resources/Texture.h"

class Game {
private:
    const std::string NAME = "Terre";

    static SDL_Window* window;
    static SDL_GLContext context;
    static unsigned int windowWidth;
    static unsigned int windowHeight;

    static std::vector<std::pair<bool, ui::Panel*>> panels;
    static Uint64 computeStart;

    static void init();
    static void run();

    static void compute(double deltaTime);
    static void render();

    static void initializeSDL();
    static void createWindow();
    static void setupOpenGLContext();
    static void launchGame();
    static void quitGame();
public:
    static void launch();
    static void cleanup();
};


#endif //TERRE_GAME_H
