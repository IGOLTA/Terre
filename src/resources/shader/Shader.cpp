#include "Shader.hpp"

namespace resources {
    Shader::Shader(std::string source, ShaderType type) : type(type) {
        createGlShader(loadSourceCode(source));
    }

    Shader::operator unsigned int() const {
        return shaderId;
    }

    void Shader::createGlShader(std::vector<char> source) {


        switch (type) {
            case VERTEX:
                shaderId = gl::glCreateShader(gl::GL_VERTEX_SHADER);
                break;
            case FRAGMENT:
                shaderId = gl::glCreateShader(gl::GL_FRAGMENT_SHADER);
                break;
            default:
                throw std::runtime_error("Unsupported shader type " + type);
        }

        char *shaderSource = &source[0];
        int size = source.size();


        gl::glShaderSource(shaderId, 1, &shaderSource, &size);
        gl::glCompileShader(shaderId);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderId, gl::GL_COMPILE_STATUS, &success);

        if (!success) {
            gl::glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            throw std::runtime_error("Failed to compile shader " + std::string(infoLog));
        }
    }

    std::vector<char> Shader::loadSourceCode(std::string file) {
        std::ifstream sourceStream(file, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);

        if (!sourceStream.is_open())
            throw std::runtime_error("Failed to access shader source code for shader " + file);

        int size = sourceStream.tellg();

        std::vector<char> buffer;
        buffer.resize(size);

        sourceStream.seekg(0);

        sourceStream.read(buffer.data(), size);

        sourceStream.close();

        return buffer;
    }

    Shader::~Shader() {
        gl::glDeleteShader(shaderId);
    }

    Shader::ShaderType Shader::getType() const {
        return type;
    }
}