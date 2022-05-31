//
// Created by louis on 20/05/22.
//

#include "Mesh.h"

namespace resources {
    Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices) :
    vertices(vertices),
    indices(indices)
    {
        indicesSize = indices.size();

        gl::glGenVertexArrays(1, &VAO);
        gl::glGenBuffers(1, &VBO);
        gl::glGenBuffers(1, &EBO);

        gl::glBindVertexArray(VAO);

        glBindBuffer(gl::GL_ARRAY_BUFFER, VBO);
        glBufferData(gl::GL_ARRAY_BUFFER, vertices.size() * sizeof(float), this->vertices.data(), gl::GL_STATIC_DRAW);

        glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(gl::GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), this->indices.data(), gl::GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, 5 * sizeof(float), (void *)0);
        gl::glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, gl::GL_FLOAT, gl::GL_FALSE, 5 * sizeof(float), (void *)(3*sizeof(float)));
        gl::glEnableVertexAttribArray(1);

        gl::glBindVertexArray(0);
    }

    Mesh::operator unsigned int() const {
        return VAO;
    }

    unsigned int Mesh::getIndicesSize() {
        return indicesSize;
    }


    Mesh::~Mesh() {
        gl::glDeleteBuffers(1, &EBO);
        gl::glDeleteBuffers(1, &VBO);
        gl::glDeleteVertexArrays(1, &VAO);
    }
}