#pragma once

#include "Mesh.h"

#include <iostream>
#include <filesystem>
#include "Texture.h"
#include "Shader.h"

Mesh::Mesh()
	: name("Unnamed Mesh")
{    
    vertexBuffer = std::make_unique<render::VertexBuffer>();
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
    vertexBuffer->draw(static_cast<int>(indices.size()));

    // Unbind textures
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::setupMesh()
{
    vertexBuffer->setVertexData(vertices, indices);
}

