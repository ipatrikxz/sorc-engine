#pragma once

#include "EditorPanel.h"

#include "Util.hpp"
#include <functional>
#include "Scene.h"
#include "core/Camera.h"

namespace ui 
{
    void EditorPanel::render(Scene& scene)
    {
        ImGui::Begin("Properties");

        if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
        {
            // import Mesh dialog
            if (ImGui::Button("Open Mesh..."))
            {
                fileDialog.Open();
            }

            ImGui::SameLine(0, 5.0f);
            ImGui::Text(currentFile.c_str());
        
			// texture file dialog
            if (ImGui::Button("Open Texture..."))
            {
                textureFileDialog.Open();
            }

            ImGui::SameLine(0, 5.0f);
            ImGui::Text(currentTextureFile.c_str());
        }

		// display mesh properties if a mesh is selected
        if (ImGui::CollapsingHeader("Scene")) 
        {
            
            DirLight& dirLight = scene.getDirLight();
            
			// destruct direction vector
            float dir[3] = { dirLight.direction.x, dirLight.direction.y, dirLight.direction.z };

            ImGui::Separator();
            ImGui::Text("Directional Light");

            if (ImGui::DragFloat3("direction", dir, 0.01f, -1.0f, 1.0f, "%.3f"))
            {
				dirLight.direction = glm::vec3(dir[0], dir[1], dir[2]);
                scene.setDirLight(dirLight);
            }
            ImGui::Separator();
            
        }

        if (ImGui::CollapsingHeader("Camera"))
        {
            ImGui::Separator();
            ImGui::Text("Location");
            ImGui::Separator();
			ImGui::Text("X: %.2f", scene.getCamera()->getLocation().x);
			ImGui::Text("Y: %.2f", scene.getCamera()->getLocation().y);
			ImGui::Text("Z: %.2f", scene.getCamera()->getLocation().z);

            ImGui::Separator();
            ImGui::Text("Rotation");
            ImGui::Separator();
            ImGui::Text("Pitch: %.2f", scene.getCamera()->getRotation().x);
            ImGui::Text("Yaw: %.2f", scene.getCamera()->getRotation().y);
            ImGui::Text("Roll: %.2f", scene.getCamera()->getRotation().z);
        }

        if (ImGui::CollapsingHeader("Performance"))
        {
            ImGuiIO io = ImGui::GetIO();
			float fps = io.Framerate;

            ImGui::Separator();
            ImGui::Text("Framerate: %.2f", fps);
        }

        ImGui::End();

        // handle mesh file dialog
        fileDialog.Display();
        if (fileDialog.HasSelected())
        {
            auto file_path = fileDialog.GetSelected().string();
            currentFile = file_path.substr(file_path.find_last_of("/\\") + 1);
            meshLoadCallback(file_path);
            fileDialog.ClearSelected();
        }

        // handle texture file dialog
        textureFileDialog.Display();
        if (textureFileDialog.HasSelected())
        {
            auto texture_path = textureFileDialog.GetSelected().string();
            currentTextureFile = texture_path.substr(texture_path.find_last_of("/\\") + 1);
            textureLoadCallback(texture_path);
            textureFileDialog.ClearSelected();
        }
    }
}