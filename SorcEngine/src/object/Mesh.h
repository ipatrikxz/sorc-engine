#pragma once

#include "Util.hpp"
#include <vector>
#include <string>

class Shader;
class Texture;

class Mesh {
public:
    Mesh();

    void draw(Shader& shader);
    void setupMesh();

    const std::string& getName() const { return name; }

    std::vector<Vertex>& getVertices() { return vertices; }
    std::vector<unsigned int>& getIndices() { return indices; }
    Material& getMaterial() { return material; }
    std::vector<Texture*>& getTextures() { return textures; }

    void setMaterial(const Material& mat) { material = mat; }
    void setTransform(const Transform& transform) { this->transform = transform; }
    void setName(const std::string& name) { this->name = name; }

private:
    std::string name;

    Transform transform;
    Material material;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    unsigned int VAO, VBO, EBO;
};