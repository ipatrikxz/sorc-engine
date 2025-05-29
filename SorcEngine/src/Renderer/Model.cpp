#include "Model.h"
#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include <../../vendor/tinyobjloader/tiny_obj_loader.h>


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

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
        std::cout << "Failed to load model: " << warn << err << std::endl;
        return;
    }

    for (const auto& shape : shapes) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

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
                    attrib.texcoords[2 * index.texcoord_index + 1]
                };
            }
            vertices.push_back(vertex);

            // Fix: Explicitly cast size_t to unsigned int with bounds checking
            size_t indexCount = indices.size();
            assert(indexCount <= std::numeric_limits<unsigned int>::max() && "Index count exceeds unsigned int limit");
            indices.push_back(static_cast<unsigned int>(indexCount));
        }

        meshes.emplace_back(vertices, indices);
    }
}

void Model::Draw(Shader& shader)
{
    for (auto& mesh : meshes) {
        mesh.Draw(shader);
    }
}