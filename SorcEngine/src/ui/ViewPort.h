#pragma once

#include "render/FrameBuffer.h"

namespace ui { class Scene; }

/* 
* Viewport is a ui component 
* Responsible for rendering a scene
*/
namespace ui 
{

    class ViewPort 
    {

    public:

        ViewPort();
        ~ViewPort() {};

        void render(Scene& scene);
        void resize(int width, int height);

        float getDeltaTime() const { return deltaTime; }

    private:
        
        std::unique_ptr<render::FrameBuffer> frameBuffer;

        float sizeX;
        float sizeY;
        float deltaTime;
        
        void updateDeltaTime();
    };

}