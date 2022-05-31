#ifndef OPENGL_CAVE_GENERATION_PROGRAM_H
#define OPENGL_CAVE_GENERATION_PROGRAM_H

#include "Shader.hpp"
#include <glad/glad.h>


namespace resources {
    class Program {
    public:
        Program(Shader* vertex, Shader* fragment);
        ~Program();

        operator unsigned int() const;

        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string &name, float value);
    private:
        unsigned int programId;
    };

}


#endif //OPENGL_CAVE_GENERATION_PROGRAM_H
