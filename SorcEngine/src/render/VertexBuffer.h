#pragma once

#include "RenderBase.h"
#include <vector>

namespace render 
{
    class VertexBuffer : public IVertexBuffer 
    {

    public:

        // IVertexBuffer interface
        void create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) override;
        void destroy() override;
        void bind() override;
        void unbind() override;
        void draw(int indexCount) override;

        // Lazy initialization
        void setVertexData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        void ensureInitialized();

    private:
        std::vector<Vertex> cachedVertices;
        std::vector<unsigned int> cachedIndices;
        bool isInitialized = false;
    };

}