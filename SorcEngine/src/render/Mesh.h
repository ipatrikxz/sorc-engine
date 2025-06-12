#pragma once

#include "Util.hpp"

class Texture;
class Shader;

namespace render {
class Mesh 
{

public:

    Mesh(std::vector<Vertex> vertices, 
        std::vector<unsigned int> indices, 
        std::vector<Texture*> textures = {}
    );
    
    void draw(Shader& shader);
    void SetupMesh();

private:

    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

};
}
