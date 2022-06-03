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
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <terre-engine/level/Tilemap.h>
#include <terre-engine/resources/shader/ShaderLoader.h>
#include <terre-engine/ui/Panel.h>
#include <terre-engine/resources/Texture.h>

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

    static void compute(double deltaTime, const SDL_Event*  e);
    static void render();

    static void initializeSDL();
    static void createWindow();
    static void setupOpenGLContext();
    static void launchGame();
    static void quitGame();
    static void eventsHandling(const SDL_Event* e);
    static void windowEvents(const SDL_Event* e);
public:
    static void launch();
    static void cleanup();
};


#endif //TERRE_GAME_H
