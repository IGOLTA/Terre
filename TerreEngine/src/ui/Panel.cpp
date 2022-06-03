//
// Created by louis on 18/05/22.
//

#include <terre-engine/ui/Panel.h>

void ui::Panel::addElement(Element *element) {
    elements.push_back(element);
}

void ui::Panel::update(double deltaTime, const SDL_Event*  e) {
    for(auto it = elements.begin();it != elements.end(); it++) (*it)->update(deltaTime, e);

    switch (e->type) {
        case SDL_MOUSEBUTTONDOWN:
            mouseButtonDown(e);
            break;
        case SDL_MOUSEBUTTONUP:
            mouseButtonUp(e);
            break;
    }
}

void ui::Panel::mouseButtonDown(const SDL_Event *e) {
    switch (e->button.button) {
        case SDL_BUTTON_LEFT:
            lastLeftMouseDownX = e->button.x;
            lastLeftMouseDownY = e->button.y;
            break;
    }
}

void ui::Panel::mouseButtonUp(const SDL_Event *e) {
    switch (e->button.button) {
        case SDL_BUTTON_LEFT:
            std::array<float, 2> press = windowToViewportCoords(lastLeftMouseDownX, lastLeftMouseDownY);
            std::array<float, 2> release = windowToViewportCoords(e->button.x, e->button.y);



            Element* finalElement = nullptr;

            for(auto it = elements.begin();it != elements.end(); it++) {
                Element* element = (*it);
                if(
                        element->getXRatio() < press[0] &&
                        element->getYRatio() < press[1] &&
                        element->getXRatio() + element->getWidthRatio() > press[0] &&
                        element->getYRatio() + element->getHeightRatio() > press[1] &&

                        element->getXRatio() < release[0] &&
                        element->getYRatio() < release[1] &&
                        element->getXRatio() + element->getWidthRatio() > release[0] &&
                        element->getYRatio() + element->getHeightRatio() > release[1]
                ) {
                    if(finalElement != nullptr) {
                        if (finalElement->getZIndex() < element->getZIndex())
                            finalElement = element;
                    } else {
                        finalElement = element;
                    }
                }
            }

            if(finalElement){
                float coords[4] = {press[0], press[1], release[0], release[1]};
                this->eventCallback(finalElement, PanelEvent::LEFT_CLICKED, coords);
            }

            break;
    }
}

std::array<float, 2> ui::Panel::windowToViewportCoords(int x, int y) {
    float fx = (static_cast<float>(x) / *this->width) * 2 - 1;
    float fy = -(static_cast<float>(y) / *this->width) * 2 + 1;

    std::array<float, 2> out = {fx, fy};

    return out;
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

void ui::Panel::eventCallback(Element* e, PanelEvent event, void* data) {

}

const unsigned int* ui::Panel::getWidth() {
    return width;
}

const unsigned int *ui::Panel::getHeight() {
    return height;
}