//
// Created by louis on 24/05/22.
//

#ifndef TERRE_SHADERLOADER_H
#define TERRE_SHADERLOADER_H

#include <string>
#include <map>
#include <utility>
#include <filesystem>

#include "Program.hpp"

namespace resources {
    class ShaderLoader {
    private:
        static bool shadersLoadeds;
        static std::map<std::string, Program*> programs;
    public:
        static void loadShaders(std::string shadersPath);
        static void unLoadShaders();

        static const std::map<std::string, Program*> getPrograms();
    };
}


#endif //TERRE_SHADERLOADER_H
