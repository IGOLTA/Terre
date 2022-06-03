//
// Created by louis on 20/05/22.
//

#include <terre-engine/resources/Mesh.h>

namespace resources {
    Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices) :
    vertices(vertices),
    indices(indices)
    {
        indicesSize = indices.size();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    Mesh::operator unsigned int() const {
        return VAO;
    }

    unsigned int Mesh::getIndicesSize() {
        return indicesSize;
    }


    Mesh::~Mesh() {
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
}