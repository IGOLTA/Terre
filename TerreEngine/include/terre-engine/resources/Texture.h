//
// Created by louis on 18/05/22.
//

#ifndef TERRE_TEXTURE_H
#define TERRE_TEXTURE_H

#include <string>
#include <stdexcept>
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

namespace resources {
    enum class TextureType {
        SPRITE,
        UI
    };
    class Texture {
    private:
        const std::string texturesRoot = "resources/textures/";

        unsigned int glTexture;
        std::string name;
        float aspectRatio;
    public:
        Texture(std::string path, TextureType type);
        ~Texture();

        std::string getName() const;

        operator unsigned int() const;
        Texture& operator=(const Texture& other);
        float getAspectRatio();
    };
}


#endif //TERRE_TEXTURE_H
