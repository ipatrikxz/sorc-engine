#pragma once

#include "RenderBase.h"

namespace render 
{
    class FrameBuffer : public render::IFrameBuffer 
    {

    public:

        // IFrameBuffer interface
        void create(int width, int height) override;
        void destroy() override;
        void bind() override;
        void unbind() override;

        void resize(int width, int height);
        
        unsigned int getTexture() override;
    };

}