//
// Created by louis on 18/05/22.
//

#ifndef TERRE_PANEL_H
#define TERRE_PANEL_H

#include <vector>
#include <SDL2/SDL.h>

#include "elements/Element.h"

namespace ui {
    class Element;
    class Panel {
    private:
        const unsigned int* width;
        const unsigned int* height;
        std::vector<Element*> elements;

    protected:
        void addElement(Element* element);
        Element* getElement(std::string name);
    public:
        Panel(const unsigned int* width, const unsigned int* height);

        const unsigned int* getWidth();
        const unsigned int* getHeight();

        virtual void elementEventCallback(std::string name, std::string event, std::vector<char> data);

        void update(double deltaTime, const SDL_Event*  e);
        void draw();

        ~Panel();
    };
}

#endif //TERRE_PANEL_H