
#include "Engine.h"

#include "Common.h"
#include "window/Window.h"
#include "render/Renderer.h"

namespace app
{
    Engine::Engine() {}

    bool Engine::init(int width, int height, const std::string& title)
    {
        showToastMessage();

        if (!window.init(width, height, title)) return false;
        if (!renderer.init(window)) return false;
        if (!uiContext.init(window)) return false;

        // bind callbacks
        window.setResizeCallback([&](int w, int h) { uiContext.getSceneView()->resize(w, h); });

        // TODO Abstract this
        inputManager.bindAction("moveCameraForward", [&](float dt) { uiContext.getScene()->getCamera()->moveForward(dt); });
        inputManager.bindAction("moveCameraBackward", [&](float dt) { uiContext.getScene()->getCamera()->moveBackward(dt); });
        inputManager.bindAction("moveCameraRight", [&](float dt) { uiContext.getScene()->getCamera()->moveRight(dt); });
        inputManager.bindAction("moveCameraLeft", [&](float dt) { uiContext.getScene()->getCamera()->moveLeft(dt); });
        inputManager.bindAction("moveCameraUp", [&](float dt) { uiContext.getScene()->getCamera()->moveUp(dt); });
        inputManager.bindAction("moveCameraDown", [&](float dt) { uiContext.getScene()->getCamera()->moveDown(dt); });
        //inputManager.bindCameraMoveAction("moveCamera", [&](float dt, int dir) { sceneCamera->moveCamera(dt, dir); });
        inputManager.bindAction("toggleCursor", [&](float) { window.toggleCursor(); });

        return true;
    }

    void Engine::run() 
    {

        if (!init(1280, 720, "Sorc Engine - Main Window")) 
        {
            return;
        }

        while (window.getIsRunning()) 
        {
            float deltaTime = uiContext.getSceneView()->getDeltaTime();
            
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
    }

    void Engine::showToastMessage()
    {
        std::cout << "Welcome to Sorc Engine!\n Version: 1.0.0          \n";
        std::cout << "-----------------------------------------         \n";
        std::cout << "Failure is an illusion.                           \n";
        std::cout << "You are your own worst enemy.		                \n";
        std::cout << "-----------------------------------------         \n";
    }

    Engine::~Engine()
    {
        uiContext.destroy();
        renderer.destroy();
        window.cleanup();
    }

}

