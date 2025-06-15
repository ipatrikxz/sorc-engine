#include "VertexBuffer.h"

#include <glad/glad.h>
#include <stdexcept>

namespace render 
{
    void VertexBuffer::create(const std::vector<sVertex>& vertices, const std::vector<unsigned int>& indices) 
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(sVertex), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, normal));
        glBindVertexArray(0);

        if (glGetError() != GL_NO_ERROR) {
            throw std::runtime_error("Failed to create vertex buffer");
        }
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
        glBindVertexArray(vao);
    }

    void VertexBuffer::unbind() 
    {
        glBindVertexArray(0);
    }

    void VertexBuffer::draw(int indexCount) 
    {
        bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        unbind();
    }
}