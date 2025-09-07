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
    
    // Material management
    Material& getMaterial(size_t meshIndex) { return materials[meshIndex]; }
    const Material& getMaterial(size_t meshIndex) const { return materials[meshIndex]; }
    void setMaterial(size_t meshIndex, const Material& material) { materials[meshIndex] = material; }
    size_t getMaterialCount() const { return materials.size(); }

    Texture* isTextureLoaded(const std::string& texturePath) const;
    Texture* loadAndCacheTexture(const std::string& texturePath, const std::string& textureName, TextureType textureType);

private:
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);


    std::string directory;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<Material> materials;  // One material per mesh
    std::unordered_map<std::string, Texture*> textureCache;

};