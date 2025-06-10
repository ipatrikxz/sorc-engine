#pragma once

#include "window/RenderWindow.h"
#include "render/Renderer.h"
#include "ui/UIContext.h"
#include "scene/Scene.h"
#include "input/InputManager.h"

#include <string>

namespace app 
{
    class Engine 
    {

    public:

        Engine();
        ~Engine();
        
        void run();

    private:

        window::RenderWindow window;
        render::Renderer renderer;
        ui::UIContext uiContext;

        // components
        scene::Scene scene;
        input::InputManager inputManager;

        bool initialize(int width, int height, const std::string& title);
    };
}
