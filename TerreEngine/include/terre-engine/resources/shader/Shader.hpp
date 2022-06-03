#ifndef OPENGL_CAVE_GENERATION_SHADER_H
#define OPENGL_CAVE_GENERATION_SHADER_H

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <glad/glad.h>

namespace resources {
    class Shader {
    public:
        enum ShaderType {
            VERTEX,
            FRAGMENT
        };

    public:
        Shader(std::string sourceCode, ShaderType type);

        ~Shader();

        ShaderType getType() const;

        operator unsigned int() const;

    private:
        unsigned int shaderId;
        ShaderType type;

    private:
        static std::vector<char> loadSourceCode(std::string file);

        void createGlShader(std::vector<char> source);
    };
}

#endif //OPENGL_CAVE_GENERATION_SHADER_H
