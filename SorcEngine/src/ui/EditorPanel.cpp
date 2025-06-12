#pragma once

#include "EditorPanel.h"
#include <functional>
#include "Scene.h"

namespace ui 
{
    void EditorPanel::render(Scene& scene)
    {
        std::shared_ptr shader = scene.getActiveShader();

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

        if (ImGui::CollapsingHeader("Material") && shader)
        {
            ImGui::ColorPicker3("Color", (float*)&shaderColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
            //ImGui::SliderFloat("Roughness", &mesh->mRoughness, 0.0f, 1.0f);
            //ImGui::SliderFloat("Metallic", &mesh->mMetallic, 0.0f, 1.0f);
            shader->setVec3("color", shaderColor);
        }

        if (ImGui::CollapsingHeader("Light"))
        {

            ImGui::Separator();
            ImGui::Text("Position");
            ImGui::Separator();
            //nimgui::draw_vec3_widget("Position", scene_view->get_light()->mPosition, 80.0f);
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