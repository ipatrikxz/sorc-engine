#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "../Common.h"

class Mesh {
private:
    GLuint vao, vbo, ebo;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Draw(Shader& shader);
    void SetupMesh();
};