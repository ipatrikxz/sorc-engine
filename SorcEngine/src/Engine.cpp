
#include "Engine.h"

#include "Util.hpp"
#include "Common.h"
#include "Core/GL.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Core/UI.h"

namespace app
{
    Engine::Engine() {}

    bool Engine::initialize(int width, int height, const std::string& title)
    {
        std::cout << "Welcome to Sorc Engine!\n Version: 1.0.0 \n-------------------------------\n";
        std::cout << "Failure is an illusion.            \n";
        std::cout << "You are your own worst enemy.		\n";

        if (!window.initialize(width, height, title)) {
            std::cerr << "Failed to initialize window\n";
            return false;
        }
        if (!renderer.initialize(window.getNativeWindow())) {
            std::cerr << "Failed to initialize renderer\n";
            return false;
        }
        if (!uiContext.initialize(window)) {
            std::cerr << "Failed to initialize UI\n";
            return false;
        }

        /*
        window.setResizeCallback([&](int w, int h) { uiContext.getSceneView()->resize(w, h); });
        window.setKeyCallback([&](int key, int scancode, int action, int mods) {
            inputManager.processKey(key, scancode, action, mods);
            });
        inputManager.bindAction("moveCameraForward", [&](float dt) { scene.getCamera()->moveForward(dt); });
        inputManager.bindAction("moveCameraBackward", [&](float dt) { scene.getCamera()->moveBackward(dt); });
        inputManager.bindAction("toggleCursor", [&](float) { window.toggleCursor(); });
        */

        return true;
    }

    Engine::~Engine() {
        uiContext.destroy();
        renderer.destroy();
        window.cleanup();
    }

    void Engine::run() {

        if (!initialize(1280, 720, "Sorc Engine - Main Window")) {
            return;
        }

        while (window.getIsRunning()) {
            float deltaTime = uiContext.getSceneView()->getDeltaTime();
            inputManager.setDeltaTime(deltaTime);
            inputManager.processInput(window);
            scene.update();
            renderer.preRender();
            uiContext.preRender();
            uiContext.render(scene);
            uiContext.postRender();
            renderer.postRender();
            window.swapBuffers();
            window.processEvents();
        }
    }




