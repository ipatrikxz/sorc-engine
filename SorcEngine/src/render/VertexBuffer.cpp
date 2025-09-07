#include "VertexBuffer.h"

#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

namespace render 
{
    void VertexBuffer::create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) 
    {
        setVertexData(vertices, indices);
        ensureInitialized();
    }

    void VertexBuffer::setVertexData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        cachedVertices = vertices;
        cachedIndices = indices;
        isInitialized = false;
    }

    void VertexBuffer::ensureInitialized()
    {
        if (isInitialized || cachedVertices.empty() || cachedIndices.empty()) {
            return;
        }

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, cachedVertices.size() * sizeof(Vertex), cachedVertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cachedIndices.size() * sizeof(unsigned int), cachedIndices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glBindVertexArray(0);

        // todo - log errors?
        
        isInitialized = true;
    }

    void VertexBuffer::destroy() 
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        vao = vbo = ibo = 0;
    }

    void VertexBuffer::bind() 
    {
        ensureInitialized();
        glBindVertexArray(vao);
    }

    void VertexBuffer::unbind() 
    {
        glBindVertexArray(0);
    }

    void VertexBuffer::draw(int indexCount) 
    {
        ensureInitialized();
        bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        unbind();
    }
}