//
// Created by louis on 18/05/22.
//

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

resources::Texture::operator unsigned int() const {
    return glTexture;
}

std::string resources::Texture::getName() const {
    return name;
}

resources::Texture::~Texture() {
    gl::glDeleteTextures(1, &glTexture);
}

resources::Texture &resources::Texture::operator=(const Texture &other) {
    if(this != &other){
        this->name = other.name;
        gl::glDeleteTextures(1, &glTexture);
        this->glTexture = other.glTexture;
    }
    return *this;
}

float resources::Texture::getAspectRatio() {
    return aspectRatio;
}

resources::Texture::Texture(std::string path, TextureType type = TextureType::SPRITE) {
    this->name = path;

    std::string fullPath = texturesRoot + path;

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);

    aspectRatio = static_cast<float>(width)/height;

    if(!data) throw std::runtime_error("Failed to load texture " + path);

    gl::glGenTextures(1, &glTexture);
    glBindTexture(gl::GL_TEXTURE_2D, glTexture);

    switch (type) {
        case TextureType::SPRITE:
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_S, gl::GL_REPEAT);
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_T, gl::GL_REPEAT);
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, gl::GL_NEAREST);
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, gl::GL_NEAREST);
            break;
        case TextureType::UI:
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_S, gl::GL_CLAMP_TO_BORDER);
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_T, gl::GL_CLAMP_TO_BORDER);
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
            glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);

            float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
            glTexParameterfv(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_BORDER_COLOR, borderColor);
            break;
    }

    switch (nrChannels) {
        case 1:
            glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RED, width, height, 0, gl::GL_RED, gl::GL_UNSIGNED_BYTE, data);
            break;
        case 2:
            glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RG, width, height, 0, gl::GL_RG, gl::GL_UNSIGNED_BYTE, data);
            break;
        case 3:
            glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RGB, width, height, 0, gl::GL_RGB, gl::GL_UNSIGNED_BYTE, data);
            break;
        case 4:
            glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RGBA, width, height, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, data);
            break;
    }

    stbi_image_free(data);
}