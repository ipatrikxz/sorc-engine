#pragma once

#include "window/Window.h"
#include "SceneView.h"
#include "Scene.h"
#include "EditorPanel.h"

namespace input {
	class InputManager;
}

namespace ui 
{

    class UIContext 
    {
    
    public:
    
        UIContext();
        ~UIContext() = default;

        bool init(window::RenderWindow& window);
        bool initInput(input::InputManager& inputManager);
        void preRender();
        void render();
        void postRender();
        void destroy();

        SceneView* getSceneView() { return sceneView.get(); }
		Scene* getScene() { return scene.get(); }

    private:
        
        // window
        std::unique_ptr<SceneView> sceneView;

		// ui elements
        std::unique_ptr<Scene> scene;
        std::unique_ptr<EditorPanel> editorPanel;

    };
}