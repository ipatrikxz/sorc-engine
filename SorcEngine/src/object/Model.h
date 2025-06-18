#pragma once

#include "Mesh.h"

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <assimp/scene.h>

enum TextureType;

class Model 
{

public:
    Model() = default;
    ~Model();

    bool load(const std::string& filepath);
    void draw(Shader& shader);

    void loadTexture(const std::string& filepath);

    const std::vector<std::shared_ptr<Mesh>>& getMeshes() const { return meshes; }
    const std::string& getDirectory() const { return directory; }

    Texture* isTextureLoaded(const std::string& texturePath) const;
    Texture* loadAndCacheTexture(const std::string& texturePath, const std::string& textureName, TextureType textureType);

private:
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);


    std::string directory;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::unordered_map<std::string, Texture*> textureCache;

};