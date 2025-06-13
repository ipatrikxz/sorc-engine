#pragma once

#include "RenderBase.h"

class RenderWindow;

namespace render 
{
    class Renderer : public RenderContext 
    {
    
    public:

		Renderer() = default;
		~Renderer() override = default;

        bool init(window::RenderWindow& windowHandle) override;
        void preRender() override;
        void postRender() override;
        void destroy() override;
    
    };
}