//
// Created by louis on 19/05/22.
//

#ifndef TERRE_ELEMENT_H
#define TERRE_ELEMENT_H

#include <string>

#include "../Panel.h"

namespace ui {
    class Panel;
    class Element {
    private:
        float xRatio = -1, yRatio = -1, widthRatio = 2, heightRatio = 2;
        int zIndex;

        Panel* parent;
        std::string name;
    protected:
        Panel* getParent();
        virtual void refreshSize();
    public:
        std::string getName();

        void setXRatio(float x);
        void setYRatio(float y);

        void setZIndex(int z);

        float getXRatio();
        float getYRatio();

        int getZIndex();

        void setWidthRatio(float x);
        void setHeightRatio(float y);

        float getWidthRatio();
        float getHeightRatio();

        Element(Panel* parent, std::string name);

        virtual void update(double deltaTime, const SDL_Event*  e);
        virtual void draw();
    };
}

#endif //TERRE_ELEMENT_H
