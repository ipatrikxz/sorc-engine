#pragma once

#include "Mesh.h"

#include <iostream>
#include <filesystem>
#include "Texture.h"
#include "Shader.h"

// Include Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh()
{
    vao = 0;
    material.color = { 1.0f, 1.0f, 1.0f };  // Default white color
    material.roughness = 0.5f;              // Default roughness
    material.metallic = 0.5f;               // Default metallic
	material.ao = 0.5f;                     // Default ambient occlusion
}

Mesh::~Mesh()
{
    for (auto* texture : textures) {
        delete texture;
    }
    glDeleteVertexArrays(1, &vao);
}


void Mesh::draw(Shader& shader)
{
    //shader.use();
    shader.setMat4("model", transform.to_mat4());

    // Set PBR material parameters
    shader.setVec3("albedo_color", material.color);
    shader.setFloat("metallic", material.metallic);
    shader.setFloat("roughness", material.roughness);
    shader.setFloat("ao", material.ao);

    if (!textures.empty()) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]->GetID());
        shader.setInt("albedo_color_texture", 0);
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(sVertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, uv));
    glBindVertexArray(0);
}

bool Mesh::load(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals
    );

    directory = std::filesystem::path(path).parent_path().string();
    name = std::filesystem::path(path).filename().string();
    std::cout << "Loading Mesh: " << name << std::endl;

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Failed to load model: " << importer.GetErrorString() << std::endl;
        return false;
    }

    // Process first mesh (simplified for now; extend for multiple meshes if needed)
    if (scene->mNumMeshes > 0)
    {
        aiMesh* mesh = scene->mMeshes[0];

        // Process vertices
        vertices.clear();
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            sVertex vertex;
            vertex.position = {
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
            };
            if (mesh->HasNormals()) {
                vertex.normal = {
                    mesh->mNormals[i].x,
                    mesh->mNormals[i].y,
                    mesh->mNormals[i].z
                };
            }
            if (mesh->HasTextureCoords(0)) {
                vertex.uv = {
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y
                };
            }
            vertices.push_back(vertex);
        }

        // Process indices
        indices.clear();
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Process material
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
            aiColor3D color;
            if (aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
                material.color = { color.r, color.g, color.b };
            }
            float roughness, metallic;
            if (aiMat->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness) == AI_SUCCESS) {
                material.roughness = roughness;
            }
            if (aiMat->Get(AI_MATKEY_METALLIC_FACTOR, metallic) == AI_SUCCESS) {
                material.metallic = metallic;
            }

            // Load texture
            aiString texPath;
            if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
            {
                std::string texturePath = directory + "/" + texPath.C_Str();
                std::cout << "Loading texture: " << texturePath << std::endl;
                Texture* texture = new Texture(texturePath);
                textures.push_back(texture);
            }
            else {
                std::cout << "No diffuse texture found for mesh: " << name << std::endl;
                textures.clear(); // Clear textures if no diffuse texture is found
            }
        }

        setupMesh();
    }

    return true;
}
