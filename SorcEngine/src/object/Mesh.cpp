#pragma once

#include "Mesh.h"

#include <iostream>
#include <filesystem>
#include "Texture.h"
#include "Shader.h"

Mesh::Mesh()
{
    VAO = 0;
	VBO = 0;
    EBO = 0;
    
	name = "Unnamed Mesh";
    
    material.color = { 1.0f, 1.0f, 1.0f };  // Default white color
    material.roughness = 0.5f;              // Default roughness
    material.metallic = 0.5f;               // Default metallic
	material.ambient = 0.5f;                // Default ambient occlusion
}


void Mesh::draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // active proper texture unit before binding
        glActiveTexture(GL_TEXTURE0 + i); 
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name;
        TextureType type = textures[i]->getType();

        switch (type)
        {
        case DIFFUSE:
			name = "texture_diffuse";   // diffuse maps
            number = std::to_string(diffuseNr++);
            break;
        case SPECULAR:
			name = "texture_specular";  // specular maps
            number = std::to_string(specularNr++);
            break;
        case NORMAL:
			name = "texture_normal";    // normal maps
            number = std::to_string(normalNr++);
            break;
        case HEIGHT:
			name = "texture_height";    // height maps
            number = std::to_string(heightNr++);
            break;
        default:
            name = "texture_diffuse";
            break;
        }

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader._ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i]->getID());
    }

	// draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Unbind textures
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

