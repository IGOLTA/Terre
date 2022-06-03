//
// Created by louis on 17/05/22.
//

#include "Game.h"

unsigned int Game::windowWidth = 500;
unsigned int Game::windowHeight = 500;
SDL_Window* Game::window = nullptr;
SDL_GLContext Game::context;
std::vector<std::pair<bool, ui::Panel*>> Game::panels;
Uint64 Game::computeStart;

void Game::launch() {
    init();
    run();
}

void Game::init() {
    initializeSDL();
    createWindow();
    setupOpenGLContext();
}

void Game::launchGame() {
    resources::ShaderLoader::loadShaders("TerreEngine/gl-shaders");

    level::Tilemap tm;
    tm.loadTilemap("test.tm");
    tm.saveTilemap("save.tm");
}

void Game::quitGame() {
    resources::ShaderLoader::unLoadShaders();
}

void Game::initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS))
        throw std::runtime_error("Failed to initialize SDL2 " + std::string(SDL_GetError()));
}

void Game::createWindow() {
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    window = SDL_CreateWindow("Terre",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              windowWidth, windowHeight,
                              SDL_WINDOW_OPENGL);

    if (window == NULL)
        throw std::runtime_error("Failed to create window " + std::string(SDL_GetError()));
}

void Game::setupOpenGLContext() {
    context = SDL_GL_CreateContext(window);
    if (context == NULL)
        throw std::runtime_error("Failed to create GL context " + std::string(SDL_GetError()));

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    SDL_GL_SetSwapInterval(1);

    SDL_Event firstResize;
    firstResize.type = SDL_WINDOWEVENT;
    firstResize.window.type = SDL_WINDOWEVENT;
    firstResize.window.timestamp = SDL_GetTicks();
    firstResize.window.windowID = SDL_GetWindowID(window);
    firstResize.window.event = SDL_WINDOWEVENT_SIZE_CHANGED;
    firstResize.window.data1 = windowWidth;
    firstResize.window.data2 = windowHeight;

    SDL_PushEvent(&firstResize);
}

void Game::run() {
    launchGame();

    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) goto stopGameLoop;
            eventsHandling(&e);

            float deltaTime = (SDL_GetTicks64() - computeStart)/1000.0f;
            computeStart = SDL_GetTicks64();
            compute(deltaTime, &e);
        }
        render();
        SDL_GL_SwapWindow(window);
    }
    stopGameLoop:

    quitGame();
}

void Game::compute(double deltaTime, const SDL_Event*  e) {
    for(auto it = panels.begin(); it != panels.end(); it++)
        if(it->first) it->second->update(deltaTime, e);
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto it = panels.begin(); it != panels.end(); it++)
        if(it->first) it->second->draw();
}


void Game::cleanup() {
    for(auto it = panels.begin(); it != panels.end(); it++) delete it->second;
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::eventsHandling(const SDL_Event* e) {
    switch (e->type) {
        case SDL_WINDOWEVENT:
            windowEvents(e);
            break;
    }
}

void Game::windowEvents(const SDL_Event *e) {
    switch (e->window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            windowWidth = e->window.data1;
            windowHeight = e->window.data2;
            glViewport(0, 0, windowWidth, windowHeight);
    }
}
