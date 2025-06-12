#pragma once

#include "util.hpp"
#include "window/Window.h"

// TODO - Comment more

class RenderWindow;

namespace render 
{
    // Vertex Buffer interface
    class IVertexBuffer 
    {

    public:

        virtual ~IVertexBuffer() = default;
        virtual void create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) = 0;
        virtual void destroy() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void draw(int indexCount) = 0;

    protected:

        unsigned int vbo = 0;
        unsigned int vao = 0;
        unsigned int ibo = 0;
    };

    // Frame Buffer interface
    class IFrameBuffer 
    {

    public:
        
        virtual ~IFrameBuffer() = default;
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

    // Render Context
    class RenderContext 
    {
   
    public:
        
        virtual ~RenderContext() = default;
        virtual bool init(window::RenderWindow& windowHandle) = 0;
        virtual void preRender() = 0;
        virtual void postRender() = 0;
        virtual void destroy() = 0;
    };
}