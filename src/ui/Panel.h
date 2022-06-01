//
// Created by louis on 18/05/22.
//

#ifndef TERRE_PANEL_H
#define TERRE_PANEL_H

#include <vector>
#include <array>
#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <thread>

#include "elements/Element.h"

namespace ui {
    class Element;
    class Panel {
    private:
        const unsigned int* width;
        const unsigned int* height;
        std::vector<Element*> elements;

        int lastLeftMouseDownX, lastLeftMouseDownY;
        void mouseButtonDown(const SDL_Event* e);
        void mouseButtonUp(const SDL_Event* e);

        std::array<float, 2> windowToViewportCoords(int x, int y);
    protected:
        enum class PanelEvent {
            LEFT_CLICKED
        };

        virtual void eventCallback(Element*, PanelEvent event, void* data);

        void addElement(Element* element);
        Element* getElement(std::string name);
    public:
        Panel(const unsigned int* width, const unsigned int* height);

        const unsigned int* getWidth();
        const unsigned int* getHeight();

        void update(double deltaTime, const SDL_Event*  e);
        void draw();

        ~Panel();
    };
}

#endif //TERRE_PANEL_H