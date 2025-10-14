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

		// TODO: Abstract this away from the engine
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
            float deltaTime = uiContext->getDeltaTime();
            
            // update inputManager
            inputManager->setDeltaTime(deltaTime);
            inputManager->processInput(*window);

            // frame
            renderer->preRender();
            
            // context
            uiContext->preRender();
            uiContext->render();
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
        std::cout << "Welcome to Sorc Engine!\n Version: 1.0.0                  "   << std::endl;
        std::cout << "-----------------------------------------                 "   << std::endl;
		std::cout << "Don't you dare go hollow.                                 "   << std::endl;
        std::cout << "Failure is an illusion.                                   "   << std::endl;
        std::cout << "You are your own worst enemy.		                        "   << std::endl;
        std::cout << "-----------------------------------------                 "   << std::endl;
		std::cout << "I envy you at times, Nomad.                               "   << std::endl;
		std::cout << "You act in service of survival.                           "   << std::endl;
		std::cout << "You move with purpose, to protect a fragile existence.    "   << std::endl;
		std::cout << "Your mind is assaulted by reality,                        "   << std::endl;
		std::cout << "that you are a mote of dust adrift a desert without end.  "   << std::endl;
		std::cout << "Yet it shields itself with hope.                          "   << std::endl;
		std::cout << "A flimsy falsehood that halts the                         "   << std::endl;
		std::cout << "crashing truth of hopelessness all the same.              "   << std::endl;
		std::cout << "~ The Maven                                               "   << std::endl;
        std::cout << "-----------------------------------------                 "   << std::endl;
    }

}

