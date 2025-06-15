#pragma once

#include "Engine.h"

#include "Common.h"
#include "window/Window.h"
#include "render/Renderer.h"

namespace app
{
    Engine::Engine() {
        window = std::make_unique<window::RenderWindow>();
        renderer = std::make_unique<render::Renderer>();
    }

    Engine::~Engine() {
        shutDown();
    }

    bool Engine::init(int width, int height, const std::string& title)
    {
        showToastMessage();

		// Initialize the window and renderer
        if (!window->init(width, height, title)) return false;
        if (!renderer->init(*window)) return false;

		// Initialize the UI context and input manager
        uiContext = std::make_unique<ui::UIContext>();
        inputManager = std::make_unique<input::InputManager>();

        if (!uiContext->init(*window)) return false;

		// Abstract this away from the engine
        if (!uiContext->initInput(*inputManager)) return false;

        return true;
    }

    int Engine::run() 
    {

		// initialize the engine
        if (!init(SORC_WINDOW_WIDTH, SORC_WINDOW_HEIGHT, "Sorc Engine - Main Window")) 
        {
            return -1;
        }

        while (window->getIsRunning())
        {
            float deltaTime = uiContext->getSceneView()->getDeltaTime();
            
            // update inputManager
            inputManager->setDeltaTime(deltaTime);
            inputManager->processInput(*window);

            // Pre Render
            renderer->preRender();
            uiContext->preRender();
            
            // Render
            uiContext->render();
            
            // Post Render
            uiContext->postRender();
            renderer->postRender();
            
            window->swapBuffers();
            window->processEvents();
        }

        return 0;
    }

    void Engine::shutDown()
    {
        uiContext->destroy();
        renderer->destroy();
        window->cleanup();
    }

    void Engine::showToastMessage()
    {
        std::cout << "Welcome to Sorc Engine!\n Version: 1.0.0          \n";
        std::cout << "-----------------------------------------         \n";
		std::cout << "Don't you dare go hollow.                         \n";
        std::cout << "Failure is an illusion.                           \n";
        std::cout << "You are your own worst enemy.		                \n";
        std::cout << "-----------------------------------------         \n";
    }

}

