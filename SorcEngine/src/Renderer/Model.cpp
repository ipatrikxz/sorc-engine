#include "Model.h"

#include <iostream>
#include <filesystem>
#include "Texture.h"
#include "Shader.h"

// Include tinyobjloader 
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


Model::Model(const std::string& path)
{
	LoadModel(path);
}

void Model::LoadModel(const std::string& path)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    // Store directory for texture paths
    directory = std::filesystem::path(path).parent_path().string();
    std::cout << "Loading model: " << path << std::endl;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), directory.c_str())) {
        std::cout << "Failed to load model: " << warn << err << std::endl;
        return;
    }

	// Check for materials on the model
    if (materials.empty()) {
        std::cout << "Warning: No materials found in model: " << directory << std::endl;
		return;
    }

	// Process each shape in the model
    for (const auto& shape : shapes) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture*> textures;

        // Load textures for the material
        if (shape.mesh.material_ids.size() > 0 && shape.mesh.material_ids[0] >= 0) {
            auto& material = materials[shape.mesh.material_ids[0]];

			// Load diffuse texture if it exists
            if (!material.diffuse_texname.empty()) {
                std::string texturePath = directory + "/" + material.diffuse_texname;
				std::cout << "Loading texture: " << texturePath << std::endl;
                Texture* texture = new Texture(texturePath);
                textures.push_back(texture);
            }
        }

		// Process vertices and indices
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex;
            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };
            if (index.normal_index >= 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }
            if (index.texcoord_index >= 0) {
                vertex.uv = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1] // flip UV coordinates
                };
            }

            vertices.push_back(vertex);
            indices.push_back(static_cast<unsigned int>(indices.size()));
        }

        meshes.emplace_back(vertices, indices, textures);
    }
}

void Model::Draw(Shader& shader)
{
    for (auto& mesh : meshes) {
        mesh.Draw(shader);
    }
}

