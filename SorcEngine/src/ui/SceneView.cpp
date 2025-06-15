
#include "SceneView.h"
#include "Scene.h"
#include <imgui.h>

namespace ui 
{
    SceneView::SceneView()
        : sizeX(0), sizeY(0), deltaTime(0) 
    {
        frameBuffer = std::make_unique<render::FrameBuffer>();
    }

    void SceneView::render(Scene& scene) 
    {
        ImGui::Begin("Scene View");
        
        ImVec2 currentSize = ImGui::GetContentRegionAvail();
        if ((int)(currentSize.x) != (int)(sizeX) ||
            (int)(currentSize.y) != (int)(sizeY)) 
        {
            sizeX = currentSize.x;
            sizeY = currentSize.y;
            frameBuffer->resize((int)(sizeX), (int)(sizeY));
            scene.getCamera()->setAspectRatio(sizeX / sizeY);
        }

		// Bind the framebuffer
        frameBuffer->bind();

		// render the scene
        scene.render();
        
		// Unbind the framebuffer
        frameBuffer->unbind();

        ImGui::Image(frameBuffer->getTexture(), ImVec2(sizeX, sizeY), ImVec2(0, 1), ImVec2(1, 0));
        updateDeltaTime();
        ImGui::End();
    }

    void SceneView::resize(int width, int height) 
    {
        sizeX = static_cast<float>(width);
        sizeY = static_cast<float>(height);
        frameBuffer->resize(width, height);
    }

    void SceneView::updateDeltaTime() 
    {
        static float lastFrame = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
}
