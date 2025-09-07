#pragma once

#include "Util.hpp"
#include "render/VertexBuffer.h"
#include <vector>
#include <string>
#include <memory>

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
    std::vector<Texture*>& getTextures() { return textures; }

    void setTransform(const Transform& transform) { this->transform = transform; }
    void setName(const std::string& name) { this->name = name; }

private:
    std::string name;

    Transform transform;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    std::unique_ptr<render::VertexBuffer> vertexBuffer;
};