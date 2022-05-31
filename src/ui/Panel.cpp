//
// Created by louis on 18/05/22.
//

#include "Panel.h"

void ui::Panel::addElement(Element *element) {
    elements.push_back(element);
}

void ui::Panel::update(double deltaTime, const SDL_Event*  e) {
    for(auto it = elements.begin();it != elements.end(); it++) (*it)->update(deltaTime, e);
}

void ui::Panel::draw() {
    for(auto it = elements.begin();it != elements.end(); it++) (*it)->draw();
}

ui::Panel::Panel(const unsigned int* width, const unsigned int* height) {
    this->width = width;
    this->height = height;
}

ui::Panel::~Panel() {
    for(auto it = elements.begin();it != elements.end(); it++) delete *it;
}

ui::Element* ui::Panel::getElement(std::string name) {
    for(auto it = elements.begin();it != elements.end(); it++) {
        if((*it)->getName() == name) return *it;
    }

    return nullptr;
}

void ui::Panel::elementEventCallback(std::string name, std::string event) {

}

const unsigned int* ui::Panel::getWidth() {
    return width;
}

const unsigned int *ui::Panel::getHeight() {
    return height;
}