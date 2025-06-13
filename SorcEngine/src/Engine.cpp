#pragma once

#include "Engine.h"

#include "Common.h"
#include "window/Window.h"
#include "render/Renderer.h"

namespace app
{
    Engine::Engine() {}

    Engine::~Engine()
    {
        shutDown();
    }

    bool Engine::init(int width, int height, const std::string& title)
    {
        showToastMessage();

        if (!window.init(width, height, title)) return false;
        if (!renderer.init(window)) return false;
        if (!uiContext.init(window)) return false;

		Camera* camera = uiContext.getScene()->getCamera();

        // bind callbacks
        window.setResizeCallback([&](int w, int h) { uiContext.getSceneView()->resize(w, h); });
        inputManager.initInputMap(camera, window);

        return true;
    }

    int Engine::run() 
    {

        if (!init(SORC_WINDOW_WIDTH, SORC_WINDOW_HEIGHT, "Sorc Engine - Main Window")) 
        {
            return -1;
        }

        while (window.getIsRunning()) 
        {
            float deltaTime = uiContext.getSceneView()->getDeltaTime();
            
            // update inputManager
            inputManager.setDeltaTime(deltaTime);
            inputManager.processInput(window);

            // Pre Render
            renderer.preRender();
            uiContext.preRender();
            
            // Render
            uiContext.render();
            
            // Post Render
            uiContext.postRender();
            renderer.postRender();
            
            window.swapBuffers();
            window.processEvents();
        }

        return 0;
    }

    void Engine::shutDown()
    {
        uiContext.destroy();
        renderer.destroy();
        window.cleanup();
    }

    void Engine::showToastMessage()
    {
        std::cout << "Welcome to Sorc Engine!\n Version: 1.0.0          \n";
        std::cout << "-----------------------------------------         \n";
        std::cout << "Failure is an illusion.                           \n";
        std::cout << "You are your own worst enemy.		                \n";
        std::cout << "-----------------------------------------         \n";
    }

}

