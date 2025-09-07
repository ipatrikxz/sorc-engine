#pragma once

#include "window/Window.h"
#include "Scene.h"
#include "EditorPanel.h"
#include "input/InputManager.h"
#include "ViewPort.h"

namespace ui 
{

    class UIContext 
    {
    
    public:
    
        UIContext();
        ~UIContext();

        bool init(window::RenderWindow& window);
        bool initInput(input::InputManager& inputManager);
        void preRender();
        void render();
        void postRender();
        void destroy();

		Scene* getScene() { return scene.get(); }
        float getDeltaTime() const;

    private:

        void SetCustomImGuiStyle();
        
        // Viewport
        std::unique_ptr<ViewPort> viewport;

		// ui elements
        std::unique_ptr<Scene> scene;
        std::unique_ptr<EditorPanel> editorPanel;

    };
}