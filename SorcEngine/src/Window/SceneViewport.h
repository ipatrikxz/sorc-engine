#pragma once

#include "Core/Camera.h"
#include "Renderer/Model.h"
#include "Renderer/Shader.h"
#include "Core/Input.h"

/* 
* Viewport is a ui component 
* Responsible for rendering a scene
*/
class SceneRenderer
{

public:
    SceneRenderer(GLFWwindow* window) :
        mCamera(nullptr),
        mModel(nullptr),
        mShader(nullptr),
        mSize(1.0, 1.0),
        windowRef(nullptr)
	{
		mCamera = std::make_unique<Camera>(glm::vec3(-2.0f, 2.5f, 1.5f), -35.0f, -35.0f);
        windowRef = window;

        deltaTime = 0.0f;
        lastFrame = static_cast<float>(glfwGetTime());
	}

    void render();
    void resize(int32_t width, int32_t height);

    void HandleInput();

    // model
    void load_model(const std::string& filepath);
    void set_model(std::shared_ptr<Model> model) { mModel = model; }
    std::shared_ptr<Model> get_model() { return mModel; }

    // camera
    glm::mat4 GetCameraView() { return mCamera->GetViewMatrix(); }

private:
    GLFWwindow* windowRef;

	std::unique_ptr<Camera> mCamera;
    std::shared_ptr<Model> mModel;
    std::unique_ptr<Shader> mShader;
    glm::vec2 mSize;

    float deltaTime;
    float lastFrame;
    float currentFrame;

    s_CursorPos cursorPos;

    void UpdateDeltaTime() {
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

};