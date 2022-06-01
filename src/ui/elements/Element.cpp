//
// Created by louis on 19/05/22.
//

#include "Element.h"

void ui::Element::refreshSize() {

}

void ui::Element::setHeightRatio(float y) {
    this->heightRatio = y;
    refreshSize();
}

void ui::Element::setWidthRatio(float x) {
    this->widthRatio = x;
    refreshSize();
}

void ui::Element::setXRatio(float x) {
    this->xRatio = x;
    refreshSize();
}

void ui::Element::setYRatio(float y) {
    this->yRatio = y;
    refreshSize();
}

float ui::Element::getHeightRatio() {
    return heightRatio;
}

float ui::Element::getWidthRatio() {
    return widthRatio;
}

float ui::Element::getXRatio() {
    return xRatio;
}

float ui::Element::getYRatio() {
    return yRatio;
}

int ui::Element::getZIndex() {
    return zIndex;
}

void ui::Element::setZIndex(int z) {
    this->zIndex = z;
}

ui::Panel *ui::Element::getParent() {
    return parent;
}

std::string ui::Element::getName() {
    return name;
}

void ui::Element::update(double deltaTime, const SDL_Event*  e) {
    if(e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        refreshSize();
}

void ui::Element::draw() {

}

ui::Element::Element(ui::Panel* panel, std::string name) : parent(panel), name(name) {
}