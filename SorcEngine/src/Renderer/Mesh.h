#pragma once

#include <vector>
#include "Common.h"

class Texture;
class Shader;

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