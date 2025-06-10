#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

namespace render 
{

    bool Renderer::initialize(void* windowHandle) 
    {
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(windowHandle));
       
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        return true;
    }

    void Renderer::preRender() {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::postRender() {}

    void Renderer::destroy() {}

}
