#pragma once

#include "Model.h"

#include "Texture.h"

#include <iostream>
#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Model::~Model()
{
    for (auto& pair : textureCache) {
        delete pair.second;
    }
    textureCache.clear();
}

bool Model::load(const std::string& filepath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        filepath,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals
    );

    directory = std::filesystem::path(filepath).parent_path().string();
    std::cout << "Loading Model: " << filepath << std::endl;

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Failed to load model: " << importer.GetErrorString() << std::endl;
        return false;
    }

    processNode(scene->mRootNode, scene);
    return true;
}

void Model::processNode(aiNode* node, const aiScene* scene) 
{
    // Process all meshes in this node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) 
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    // Recursively process child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) 
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene) 
{
    std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>();
    std::vector<Vertex>& vertices = newMesh->getVertices();
    std::vector<unsigned int>& indices = newMesh->getIndices();

    // Process vertices
    vertices.clear();
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) 
    {
        Vertex vertex;
        vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

        if (mesh->HasNormals()) 
        {
            vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
        }
        if (mesh->HasTextureCoords(0)) 
        {
            vertex.uv = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
        }
        vertices.push_back(vertex);
    }

    // Process indices
    indices.clear();
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) 
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) 
    {
        aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
        aiColor3D diffuse;
		aiColor3D specular;
        aiColor3D ambient;
		float metallic, roughness;

        // diffuse color
        if (aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
        {
            //std::cout << "Color Diffuse: " << diffuse.r << " " << diffuse.g << " " << diffuse.b << std::endl;
        }

        // load texture
        aiString texPath;
        if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
        {
            std::string texturePath = directory + "/" + texPath.C_Str();
            std::string textureName = texPath.C_Str();

            // check cache
            Texture* texture = isTextureLoaded(texturePath);
            
			// if texture is not cached, load it
            if (!texture) 
            {
                texture = loadAndCacheTexture(texturePath, textureName, TextureType::DIFFUSE);
            }
            
			// add texture to mesh
            if (texture) 
            {
                newMesh->getTextures().push_back(texture);
            }
        }
    }

    newMesh->setupMesh();
    meshes.push_back(newMesh);
}

Texture* Model::isTextureLoaded(const std::string& texturePath) const
{
    auto it = textureCache.find(texturePath);
    return it != textureCache.end() ? it->second : nullptr;
}

Texture* Model::loadAndCacheTexture(const std::string& texturePath, const std::string& textureName, TextureType textureType)
{
    Texture* texture = new Texture();
    
    if (texture->load(texturePath)) 
    {
        texture->setType(textureType);
        texture->setPath(texturePath);
        texture->setName(textureName);
        textureCache[texturePath] = texture;
        return texture;
    }
    std::cout << "Failed to load texture: " << texturePath << std::endl;
    delete texture;
    return nullptr;
}

void Model::draw(Shader& shader) 
{
    for (auto& mesh : meshes) {
        mesh->draw(shader);
    }
}

void Model::loadTexture(const std::string& filepath)
{
    
    // Extract texture name from path
    std::string textureName = filepath.substr(filepath.find_last_of("/\\") + 1);

    // Load texture using Model's cache
    Texture* texture = isTextureLoaded(filepath);
    if (!texture) {
        texture = loadAndCacheTexture(filepath, textureName, TextureType::DIFFUSE);
    }

    if (texture) {
        // Apply texture to a meshes
        if (!meshes.empty()) {
            for (auto& mesh : meshes) {
                mesh->getTextures().push_back(texture); 
			}
        }
    }
    
}
