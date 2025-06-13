#pragma once

#include "Util.hpp"

#include <assimp/scene.h>

class Shader;
class Texture;

class Mesh {

public:

    Mesh();
    ~Mesh();

    bool load(const std::string& path);
    void draw(Shader& shader);

    const sMaterial& getMaterial() const { return material; }
    void setMaterial(const sMaterial& mat) { material = mat; }

	const std::vector<sVertex>& getVertices() const { return vertices; }
    const std::vector<unsigned int>& getIndices() const { return indices; }
    const std::vector<Texture*>& getTextures() const { return textures; }
    const sTransform& getTransform() const { return transform; }
	const std::string& getName() const { return name; }
	const std::string& getDirectory() const { return directory; }

	void setTransform(const sTransform transform) { this->transform = transform; }

private:

    void setupMesh();
    
    sTransform transform;
    sMaterial material;

    std::vector<sVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

	std::string name;
    std::string directory;

    unsigned int vao = 0;
};
