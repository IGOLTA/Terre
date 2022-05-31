#include "Program.hpp"
namespace resources {
    Program::Program(Shader* vertex, Shader* fragment) {
        programId = gl::glCreateProgram();

        gl::glAttachShader(programId, *vertex);
        gl::glAttachShader(programId, *fragment);
        gl::glLinkProgram(programId);

        delete vertex;
        delete fragment;

        int success;
        char infoLog[512];
        glGetProgramiv(programId, gl::GL_LINK_STATUS, &success);
        if (!success) {
            gl::glGetProgramInfoLog(programId, 512, NULL, infoLog);
            throw std::runtime_error("Failed to link program \n" + std::string(infoLog));
        }
    }

    void Program::setBool(const std::string &name, bool value) {
        gl::glUniform1i(gl::glGetUniformLocation(programId, name.c_str()), (int) value);
    }

    void Program::setInt(const std::string &name, int value) {
        gl::glUniform1i(gl::glGetUniformLocation(programId, name.c_str()), value);
    }

    void Program::setFloat(const std::string &name, float value) {
        gl::glUniform1f(gl::glGetUniformLocation(programId, name.c_str()), value);
    }

    Program::~Program() {

        gl::glDeleteProgram(programId);
    }

    Program::operator unsigned int() const {
        return programId;
    }
}