
#include "Window.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace nWindow {

    GL_Window::GL_Window(int width, int height, const std::string& title)
        : gl_window(nullptr), _width(width), _height(height), _title(title)
    {
    }

    bool GL_Window::Init()
    {
        if (!Init_GL())
        {
            return false;
        }

        scene_viewport = std::make_unique<SceneRenderer>(gl_window);

        return true;
    }

    void GL_Window::Render()
    {
        scene_viewport->render();
        SwapBuffersPollEvents();
    }

    bool GL_Window::Init_GL()
    {
        // Initialize GLFW
        if (!glfwInit()) return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        // Create a GLFW window
        gl_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

        // Check if the window was created successfully
        if (gl_window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        // Make the window's context current
        glfwMakeContextCurrent(gl_window);

        // chech if glad is initialized successfully
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        // Setup input mode
        SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // enable OpenGL features
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        return true;
    }

    void GL_Window::SwapBuffersPollEvents()
    {
        glfwSwapBuffers(gl_window);
        glfwPollEvents();
    }

    bool GL_Window::IsOpen()
    {
        return !glfwWindowShouldClose(gl_window);
    }

    void GL_Window::SetShouldClose(bool value)
    {
        glfwSetWindowShouldClose(gl_window, value);
    }

    void GL_Window::SetInputMode(int mode, int value)
    {
        glfwSetInputMode(gl_window, mode, value);
    }

    void GL_Window::GetFramebufferSize(int& width, int& height)
    {
        glfwGetFramebufferSize(gl_window, &width, &height);
    }

    void GL_Window::Cleanup()
    {
        glfwTerminate();
    }

   

}