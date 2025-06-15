#pragma once

#include "RenderBase.h"

namespace render 
{
    class VertexBuffer : public IVertexBuffer 
    {

    public:

        // IVertexBuffer interface
        void create(const std::vector<sVertex>& vertices, const std::vector<unsigned int>& indices) override;
        void destroy() override;
        void bind() override;
        void unbind() override;
        void draw(int indexCount) override;
    };

}