//
// Created by louis on 20/05/22.
//

#ifndef TERRE_MESH_H
#define TERRE_MESH_H

#include <vector>
#include <glbinding/gl/gl.h>
#include <iostream>

namespace resources {
    class Mesh {
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        unsigned int indicesSize;
    public:
        Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
        unsigned int getIndicesSize();
        operator unsigned int() const;
        ~Mesh();
    };
}

#endif //TERRE_MESH_H
