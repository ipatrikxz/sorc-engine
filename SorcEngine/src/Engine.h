#pragma once

#include <string>

#include "window/Window.h"
#include "input/InputManager.h"
#include "render/Renderer.h"
#include "ui/UIContext.h"
#include "ui/Scene.h"


namespace app 
{
    class Engine 
    {

    public:

        Engine();
        ~Engine();
        
        void run();
        void showToastMessage();

    private:

        window::RenderWindow window;
        render::Renderer renderer;

        // components
        ui::UIContext uiContext;
        input::InputManager inputManager;

        bool init(int width, int height, const std::string& title);
    };
}
