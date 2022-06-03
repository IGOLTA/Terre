//
// Created by louis on 02/06/22.
//

#include <terre-engine/level/Tilemap.h>

namespace level {

    Tilemap::TilemapIndexOutOfBound::TilemapIndexOutOfBound() : runtime_error("Tilemap index out of bound"){}

    Tilemap::~Tilemap() {
        for(auto it = textures.begin(); it != textures.end(); it++) if(*it) delete (*it);
    }

    void Tilemap::loadTilemap(std::filesystem::path path) {
        for(auto it = textures.begin(); it != textures.end(); it++) if(*it) delete (*it);

        std::filesystem::path tilePath = tilemapRoot / path;
        std::ifstream fileInput;
        fileInput.open(tilePath);

        if(!fileInput.is_open()) throw std::runtime_error("Failed to open tilemap at " + tilePath.generic_string());

        // Get texture paths
        while(true) {
            unsigned short pathLength;
            fileInput.read(reinterpret_cast<char *>(&pathLength), 2);

            if(pathLength == 0) break;

            std::vector<char> path;
            path.resize(pathLength);
            fileInput.read(path.data(), pathLength);

            textures.push_back(new resources::Texture(std::string(path.data()), resources::TextureType::SPRITE));
        }

        // Get map size
        fileInput.read(reinterpret_cast<char *>(&mapWidth), 2);
        fileInput.read(reinterpret_cast<char *>(&mapHeight), 2);

        map.resize(mapWidth*mapHeight*3);

        fileInput.read(reinterpret_cast<char *>(map.data()), mapWidth*mapHeight*3);
        fileInput.close();
    }

    void Tilemap::saveTilemap(std::filesystem::path path) {
        std::filesystem::path tilePath = tilemapRoot / path;
        std::ofstream fileOutput;
        fileOutput.open(tilePath);

        if(!fileOutput.is_open()) throw std::runtime_error("Failed to save tilemap at " + tilePath.generic_string());

        //Save texture paths
        for(auto it = textures.begin(); it != textures.end(); it++) {
            if(*it == nullptr) continue;
            unsigned short pathSize = (*it)->getName().length();
            fileOutput.write(reinterpret_cast<char*>(&pathSize), 2);
            fileOutput.write((*it)->getName().c_str(), (*it)->getName().length());
        }
        //End
        unsigned short pathSize = 0;
        fileOutput.write(reinterpret_cast<char*>(&pathSize), 2);

        //Save map size
        fileOutput.write(reinterpret_cast<char *>(&mapWidth), 2);
        fileOutput.write(reinterpret_cast<char *>(&mapHeight), 2);

        //Save map
        fileOutput.write(reinterpret_cast<char*>(map.data()), mapWidth * mapHeight * 3);

        fileOutput.close();
    }

    const resources::Texture* Tilemap::getTexture(unsigned  char index) {
        return textures[index];
    }

    void Tilemap::setTexture(unsigned  char index, resources::Texture* texture) {
        if(textures[index]) delete textures[index];
        textures[index] = texture;
    }
    unsigned char Tilemap::getTexturesAmount() {
        return textures.size();
    }

    void Tilemap::appendTexture(resources::Texture* texture) {
        textures.push_back(texture);
    }

    void Tilemap::setTile(unsigned short x, unsigned short y, int layer, unsigned char index) {
        if(layer != 0 && layer != 1 ) throw std::runtime_error("Only layer 0 and 1 hold textures");
        if(x >= mapWidth || y >= mapHeight) throw TilemapIndexOutOfBound();

        map[layer * mapHeight * mapWidth + x * mapHeight + y] = index;
    }

    void Tilemap::setLight(unsigned short x, unsigned short y, bool light) {
        if(x >= mapWidth || y >= mapHeight) throw TilemapIndexOutOfBound();

        map[2 * mapHeight * mapWidth + x * mapHeight + y] = light;
    }

    unsigned char Tilemap::getTile(unsigned short x, unsigned short y, int layer) {
        if(x >= mapWidth || y >= mapHeight) throw TilemapIndexOutOfBound();
        if(layer != 0 && layer != 1 ) throw std::runtime_error("Only layer 0 and 1 hold textures");

        return  map[layer * mapHeight * mapWidth + x * mapHeight + y];
    }

    bool Tilemap::hasLight(unsigned short x, unsigned short y) {
        if(x >= mapWidth || y >= mapHeight) throw TilemapIndexOutOfBound();
        return map[2 * mapHeight * mapWidth + x * mapHeight + y];
    }
}