#pragma once

#include "EditorPanel.h"

#include "Util.hpp"
#include <functional>
#include "Scene.h"

namespace ui 
{
    void EditorPanel::render(Scene& scene)
    {
        Shader* shader = scene.getActiveShader();
        Mesh* mesh = scene.getActiveMesh();

        if (!shader)
        {
            ImGui::Begin("Properties");
            ImGui::Text("No active shader!");
            ImGui::End();
            return;
        }

		// Import Mesh dialog
        ImGui::Begin("Properties");
        if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
        {

            if (ImGui::Button("Open..."))
            {
                fileDialog.Open();
            }
            ImGui::SameLine(0, 5.0f);
            ImGui::Text(currentFile.c_str());
        }

		// Display mesh properties if a mesh is selected
        if (ImGui::CollapsingHeader("Material") && mesh && shader) 
        {
            sMaterial material = mesh->getMaterial();

            if (ImGui::ColorPicker3("Color", (float*)&material.color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB)) 
            {
                mesh->setMaterial(material);
            }

            if (ImGui::SliderFloat("Roughness", &material.roughness, 0.0f, 1.0f)) 
            {
                mesh->setMaterial(material);
            }

            if (ImGui::SliderFloat("Metallic", &material.metallic, 0.0f, 1.0f)) 
            {
                mesh->setMaterial(material);
            }

            if (ImGui::SliderFloat("Ambient Occlusion", &material.ao, 0.0f, 1.0f))
            {
                mesh->setMaterial(material);
            }

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

        ImGui::End();

        fileDialog.Display();
        if (fileDialog.HasSelected())
        {
            auto file_path = fileDialog.GetSelected().string();
            currentFile = file_path.substr(file_path.find_last_of("/\\") + 1);
            meshLoadCallback(file_path);
            fileDialog.ClearSelected();
        }

    }
}