
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace window 
{
    RenderWindow::RenderWindow() :
        windowHandle(nullptr),
        isRunning(false)
    {}

    RenderWindow::~RenderWindow() 
    { 
        cleanup(); 
    }

    bool RenderWindow::init(int width, int height, const std::string& title) 
    {
        this->width = width;
        this->height = height;
        this->title = title;

        if (!glfwInit()) 
        {
            std::cerr << "Failed to initialize GLFW\n";
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!windowHandle) 
        {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(windowHandle);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
        {
            std::cerr << "Failed to initialize GLAD\n";
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Set up callbacks
        glfwSetWindowUserPointer(windowHandle, this);
        glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow* window, int w, int h) 
        {
            auto* win = static_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
            if (win->resizeCallback) 
            {
                win->resizeCallback(w, h);
            }
        });

        glfwSetKeyCallback(windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
        {
            auto* win = static_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
            if (win->keyCallback) 
            {
                win->keyCallback(key, scancode, action, mods);
            }
        });

        isRunning = true;
        return true;
    }    

    void RenderWindow::swapBuffers() 
    {
        glfwSwapBuffers(windowHandle);
    }

    void RenderWindow::toggleCursor() 
    {
        int mode = glfwGetInputMode(windowHandle, GLFW_CURSOR) == GLFW_CURSOR_DISABLED
            ? GLFW_CURSOR_NORMAL
            : GLFW_CURSOR_DISABLED;
        glfwSetInputMode(windowHandle, GLFW_CURSOR, mode);
    }

    void RenderWindow::processEvents() 
    {
        glfwPollEvents();
        isRunning = !glfwWindowShouldClose(windowHandle);
    }

    void RenderWindow::getFramebufferSize(int& width, int& height) const 
    {
        glfwGetFramebufferSize(windowHandle, &width, &height);
    }

    void RenderWindow::setShouldClose()
    {
        isRunning = false;
        glfwTerminate();
    }

    void RenderWindow::cleanup()
    {
        if (windowHandle)
        {
            glfwDestroyWindow(windowHandle);
            glfwTerminate();
        }

        windowHandle = nullptr;
        isRunning = false;
    }
}