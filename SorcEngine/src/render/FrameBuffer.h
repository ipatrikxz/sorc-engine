#pragma once

#include "RenderBase.h"

namespace render 
{
    class FrameBuffer : public render::IFrameBuffer 
    {

    public:

        // IFrameBuffer interface
        void create(int width, int height) override;
        void bind() override;
        void unbind() override;
        void destroy() override;
        unsigned int getTexture() override;

        void resize(int width, int height);
    };

}