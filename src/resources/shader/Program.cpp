#include "Program.hpp"
namespace resources {
    Program::Program(Shader* vertex, Shader* fragment) {
        programId = glCreateProgram();

        glAttachShader(programId, *vertex);
        glAttachShader(programId, *fragment);
        glLinkProgram(programId);

        delete vertex;
        delete fragment;

        int success;
        char infoLog[512];
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programId, 512, NULL, infoLog);
            throw std::runtime_error("Failed to link program \n" + std::string(infoLog));
        }
    }

    void Program::setBool(const std::string &name, bool value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), (int) value);
    }

    void Program::setInt(const std::string &name, int value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
    }

    void Program::setFloat(const std::string &name, float value) {
        glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
    }

    Program::~Program() {

        glDeleteProgram(programId);
    }

    Program::operator unsigned int() const {
        return programId;
    }
}