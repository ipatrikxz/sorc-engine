#pragma once

#include <glm/gtc/type_ptr.hpp>
#include "window/Window.h"
#include "SceneView.h"
#include "EditorPanel.h"

namespace ui 
{

    class UIContext 
    {
    
    public:
    
        UIContext();
        ~UIContext();

        bool init(window::RenderWindow& window);
        void preRender();
        void render();
        void postRender();
        void destroy();

        SceneView* getSceneView() { return sceneView.get(); }
		Scene* getScene() { return scene.get(); }

    private:
        
        std::unique_ptr<SceneView> sceneView;

        std::unique_ptr<Scene> scene;
        std::unique_ptr<EditorPanel> editorPanel;

    };
}