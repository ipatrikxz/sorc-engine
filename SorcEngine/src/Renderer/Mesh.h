#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "../Common.h"
#include "Texture.h"

class Mesh {
private:
    GLuint vao, vbo, ebo;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures = {});
    void Draw(Shader& shader);
    void SetupMesh();
};