//
// Created by louis on 18/05/22.
//

#include "Image.h"

void ui::Image::refreshSize() {


    if(texture) {
        if(mesh) delete mesh;

        std::vector<float> vertices;

        ImageFitting realFitting;

        float finalAspectRatio =  (((getWidthRatio() + 1) / 2) * (*getParent()->getWidth())) / (((getHeightRatio() + 1) / 2) * (*getParent()->getHeight()));

        switch (fitting) {
            case ImageFitting::FIT_LARGER:
                if(finalAspectRatio < texture->getAspectRatio()) {
                    realFitting = ImageFitting::FIT_VERTICALLY;
                } else {
                    realFitting = ImageFitting::FIT_HORIZONTALLY;
                }
                break;
            case ImageFitting::FIT_SMALLER:
                if(finalAspectRatio > texture->getAspectRatio()) {
                    realFitting = ImageFitting::FIT_VERTICALLY;
                } else {
                    realFitting = ImageFitting::FIT_HORIZONTALLY;
                }
                break;
            default:
                realFitting = fitting;
                break;
        }

        switch (realFitting) {
            case ImageFitting::WARP:
                vertices = {
                        // positions       // texture coords
                        getXRatio() + getWidthRatio(),  getYRatio() + getHeightRatio(), 0.0f, 1.0f, 1.0f, // top right
                        getXRatio() + getWidthRatio(), getYRatio() , 0.0f, 1.0f, 0.0f, // bottom right
                        getXRatio(), getYRatio() , 0.0f,  0.0f, 0.0f, // bottom left
                        getXRatio(),  getYRatio() + getHeightRatio(), 0.0f,  0.0f, 1.0f  // top left
                };
                break;
            case ImageFitting::FIT_HORIZONTALLY: {
                float onScreenWidth = ((getWidthRatio() + 1) / 2) * *getParent()->getWidth();
                float onScreenHeight = onScreenWidth / texture->getAspectRatio();
                float realOnScreenHeight = ((getHeightRatio() + 1) / 2) * *getParent()->getHeight();
                float ratio = realOnScreenHeight / onScreenHeight;
                float shift = (1-ratio) /2;

                vertices = {
                        // positions       // texture coords
                        getXRatio() + getWidthRatio(),  getYRatio() + getHeightRatio(), 0.0f, 1.0f, ratio+shift, // top right
                        getXRatio() + getWidthRatio(), getYRatio() , 0.0f, 1.0f, shift, // bottom right
                        getXRatio(), getYRatio() , 0.0f,  0.0f,shift, // bottom left
                        getXRatio(),  getYRatio() + getHeightRatio(), 0.0f,  0.0f, ratio+shift   // top left
                };
            }
                break;
            case ImageFitting::FIT_VERTICALLY:
                float onScreenHeight = ((getHeightRatio() + 1) / 2) * *getParent()->getHeight();
                float onScreenWidth = onScreenHeight * texture->getAspectRatio();
                float realOnScreenWidth = ((getWidthRatio() + 1) / 2) * *getParent()->getWidth();
                float ratio = realOnScreenWidth / onScreenWidth;
                float shift = (1-ratio) /2;

                vertices = {
                        // positions       // texture coords
                        getXRatio() + getWidthRatio(),  getYRatio() + getHeightRatio(), 0.0f, ratio + shift, 1.0f, // top right
                        getXRatio() + getWidthRatio(), getYRatio() , 0.0f, ratio + shift, 0.0f, // bottom right
                        getXRatio(), getYRatio() , 0.0f, shift, 0.0f, // bottom left
                        getXRatio(),  getYRatio() + getHeightRatio(), 0.0f,  shift, 1.0f  // top left
                };
                break;
        }

        std::vector<unsigned int> indices = {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
        };

        mesh = new resources::Mesh(vertices, indices);
    }
}

void ui::Image::update(double deltaTime, const SDL_Event*  e) {
    Element::update(deltaTime, e);

}

void ui::Image::draw() {
        glBindTexture(GL_TEXTURE_2D, *texture);
        resources::ShaderLoader::getPrograms().at("src/shaders/ui/unlit-image")->setInt("aTexture", 0);
        glUseProgram(*resources::ShaderLoader::getPrograms().at("src/shaders/ui/unlit-image"));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glBindVertexArray(*mesh);
        glDrawElements(GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);
}

void ui::Image::setTexture(resources::Texture* texture) {
    delete this->texture;
    this->texture = texture;
}

void ui::Image::setFitting(ImageFitting fitting) {
    refreshSize();
    this->fitting = fitting;
}

ui::Image::Image(Panel* parent, std::string name) : Element(parent, name) {}

ui::Image::~Image() {
    delete mesh;
    delete texture;
}