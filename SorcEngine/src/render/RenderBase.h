#pragma once

#include "render/Vertex.hpp"
#include <vector>

namespace render 
{
    class VertexBuffer 
    {

    public:

        virtual ~VertexBuffer() = default;
        virtual void create(const std::vector<scene::Vertex>& vertices, const std::vector<unsigned int>& indices) = 0;
        virtual void destroy() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void draw(int indexCount) = 0;

    protected:

        unsigned int vbo = 0;
        unsigned int vao = 0;
        unsigned int ibo = 0;
    };

    class FrameBuffer 
    {
    
    public:
        
        virtual ~FrameBuffer() = default;
        virtual void create(int width, int height) = 0;
        virtual void destroy() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual unsigned int getTexture() = 0;

    protected:
    
        unsigned int fbo = 0;
        unsigned int textureId = 0;
        unsigned int depthId = 0;
        int width = 0;
        int height = 0;
    };

    class RenderContext 
    {
   
    public:
        
        virtual ~RenderContext() = default;
        virtual bool initialize(void* windowHandle) = 0;
        virtual void preRender() = 0;
        virtual void postRender() = 0;
        virtual void destroy() = 0;
    };
}