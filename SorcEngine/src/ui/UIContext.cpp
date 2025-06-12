#pragma once

#include "UIContext.h"

#include <memory>
#include <string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "EditorPanel.h"

namespace ui 
{
    
    UIContext::UIContext() 
    {
		scene = std::make_unique<Scene>();
		sceneView = std::make_unique<SceneView>();
        editorPanel = std::make_unique<EditorPanel>();
    }

    UIContext::~UIContext() 
    {
        destroy();
    }

    bool UIContext::init(window::RenderWindow& window) 
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
        ImGui::GetStyle().WindowRounding = 0.0f;
        
        if (!ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window.getNativeWindow()), true)) 
        {
            std::cerr << "Failed to initialize ImGui \n";
            return false;
        }

        if (!ImGui_ImplOpenGL3_Init("#version 450")) 
        {
            std::cerr << "Failed to initialize ImGui version \n";
            return false;
        }

        scene->init();

		// setup callbacks for scene view and editor panel
        editorPanel->setMeshLoadCallback([&](const std::string& filepath) { scene->loadModel(filepath); });
        
        return true;
    }

    void UIContext::render()
    {
        sceneView->render(*scene);
        editorPanel->render(*scene);
    }

    void UIContext::preRender() 
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, windowFlags);
        ImGui::PopStyleVar(3);
        ImGui::DockSpace(ImGui::GetID("DockSpace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End();
    }

    void UIContext::postRender() 
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
        {
            GLFWwindow* backupContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupContext);
        }
    }

    void UIContext::destroy() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}