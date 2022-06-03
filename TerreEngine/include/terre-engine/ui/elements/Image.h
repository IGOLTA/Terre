//
// Created by louis on 18/05/22.
//

#ifndef TERRE_IMAGE_H
#define TERRE_IMAGE_H

#include <optional>

#include "Element.h"
#include "../../resources/Texture.h"
#include "../../resources/Mesh.h"
#include "../../resources/shader/ShaderLoader.h"

namespace ui {
    enum class ImageFitting {
        WARP,
        FIT_HORIZONTALLY,
        FIT_VERTICALLY,
        FIT_LARGER,
        FIT_SMALLER
    };
    class Image : public Element {
    private:
        resources::Texture* texture = nullptr;
        resources::Mesh* mesh = nullptr;
        ImageFitting fitting = ImageFitting::WARP;
    protected:
        void refreshSize();

    public:

        Image(Panel* parent, std::string name);
        ~Image();

        void setTexture(resources::Texture* texture);
        void setFitting(ImageFitting fitting);

        void update(double deltaTime, const SDL_Event*  e);
        void draw();
    };
}

#endif //TERRE_IMAGE_H
