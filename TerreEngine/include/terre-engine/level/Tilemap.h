//
// Created by louis on 02/06/22.
//

#ifndef TERRE_TILEMAP_H
#define TERRE_TILEMAP_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <iostream>

#include "../resources/Texture.h"

namespace level {
    class Tilemap {
    private:
        const std::filesystem::path tilemapRoot = "resources/tilemap";

        std::vector<resources::Texture*> textures;
        std::vector<unsigned char> map;

        unsigned short mapWidth, mapHeight;

    public:
        class TilemapIndexOutOfBound : public std::runtime_error {
        public:
            TilemapIndexOutOfBound();
        };

        ~Tilemap();

        void loadTilemap(std::filesystem::path path);
        void saveTilemap(std::filesystem::path path);

        const resources::Texture* getTexture(unsigned  char index);
        void setTexture(unsigned  char index, resources::Texture*);
        void appendTexture(resources::Texture*);
        unsigned char getTexturesAmount();

        void setTile(unsigned short x, unsigned short y, int layer, unsigned char index);
        void setLight(unsigned short x, unsigned short y, bool light);

        unsigned char getTile(unsigned short x, unsigned short y, int layer);
        bool hasLight(unsigned short x, unsigned short y);
    };
}

#endif //TERRE_TILEMAP_H
