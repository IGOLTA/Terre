//
// Created by louis on 24/05/22.
//

#include "ShaderLoader.h"

namespace resources {
    const std::string ShaderLoader::shadersPath = "src/shaders";
    std::map<std::string, Program*> ShaderLoader::programs;
    bool ShaderLoader::shadersLoadeds = false;

    void ShaderLoader::loadShaders() {
        if(!shadersLoadeds) {
            for(auto& p : std::filesystem::recursive_directory_iterator(shadersPath)) {
                if (p.is_directory()) {
                    if(std::filesystem::exists(p.path().generic_string() + "/shader.vert") &&
                       std::filesystem::exists(p.path().generic_string() + "/shader.frag")) {
                        auto prog = new Program(
                                new Shader( p.path().generic_string() + "/shader.vert", Shader::VERTEX),
                                new Shader( p.path().generic_string() + "/shader.frag", Shader::FRAGMENT)
                        );

                        std::string name = p.path().generic_string();

                        programs.insert(std::pair<std::string, Program*>(name, prog));
                    }
                }
            }
            shadersLoadeds = true;
        }
    }

    void ShaderLoader::unLoadShaders() {
        if(shadersLoadeds) {
            for (const auto& kv : programs) {
                delete kv.second;
            }
            programs.clear();
            shadersLoadeds = false;
        }
    }

    const std::map<std::string, Program*> ShaderLoader::getPrograms() {
        return programs;
    }
}