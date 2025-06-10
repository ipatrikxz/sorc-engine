#pragma once
#include "RenderBase.h"

struct GLFWwindow;

namespace render 
{
    class Renderer : public RenderContext 
    {
    
    public:

        bool initialize(void* windowHandle) override;
        void preRender() override;
        void postRender() override;
        void destroy() override;
    
    };
}