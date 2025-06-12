#pragma once

#include "RenderBase.h"

class RenderWindow;

namespace render 
{
    class Renderer : public RenderContext 
    {
    
    public:

        bool init(window::RenderWindow& windowHandle) override;
        void preRender() override;
        void postRender() override;
        void destroy() override;
    
    };
}