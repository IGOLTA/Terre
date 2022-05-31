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
    resources::ShaderLoader::loadShaders();

    Game::panels.push_back(std::make_pair(true, static_cast<ui::Panel*>(new ui::MainMenu(&windowWidth, &windowHeight))));
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

    glbinding::initialize([](const char * name) { return reinterpret_cast<glbinding::ProcAddress>(SDL_GL_GetProcAddress(name)); }, false);

    //SDL_GL_SetSwapInterval(1);

    gl::glViewport(0, 0, windowWidth, windowHeight);
}

void Game::run() {
    launchGame();

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        float deltaTime = (SDL_GetTicks64() - computeStart)/1000.0f;
        computeStart = SDL_GetTicks64();
        compute(deltaTime);
        render();
        SDL_GL_SwapWindow(window);

        if(e.type == SDL_QUIT) break;
    }

    quitGame();
}

void Game::compute(double deltaTime) {
    for(auto it = panels.begin(); it != panels.end(); it++)
        if(it->first) it->second->update(deltaTime);
}

void Game::render() {

    //gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

    for(auto it = panels.begin(); it != panels.end(); it++)
        if(it->first) it->second->draw();
}


void Game::cleanup() {
    for(auto it = panels.begin(); it != panels.end(); it++) delete it->second;
    SDL_DestroyWindow(window);
    SDL_Quit();
}