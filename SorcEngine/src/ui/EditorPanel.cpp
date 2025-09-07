#pragma once

#include "EditorPanel.h"

#include "Util.hpp"
#include "Scene.h"
#include "core/Camera.h"
#include "ProfilerTimeline.h"

#include <functional>

namespace ui 
{
    void EditorPanel::render(Scene& scene)
    {
        ImGui::Begin("Properties");
		    drawMeshControls(scene);
            drawLightControls(scene);
            drawCameraInfo(scene);
        ImGui::End();

        ImGui::Begin("Stats");
            drawPerformanceInfo(scene);
        ImGui::End();
    }

    // ------------------------------------------------------------------
    // mesh loading controls
    void EditorPanel::drawMeshControls(ui::Scene& scene)
    {
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

    // ------------------------------------------------------------------
    // scene lighting controls
    void EditorPanel::drawLightControls(ui::Scene& scene)
    {
        
        if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
        {

            // capture reference to directional light
            DirLight& dirLight = scene.getLights().getDirectionalLight();

            // destruct direction vector
            float dir[3] = { dirLight.direction.x, dirLight.direction.y, dirLight.direction.z };

            ImGui::Separator();
            ImGui::Text("Directional Light");

            if (ImGui::DragFloat3("direction", dir, 0.01f, -1.0f, 1.0f, "%.3f"))
            {
                dirLight.direction = glm::vec3(dir[0], dir[1], dir[2]);
            }

            // Directional Light Color Controls
            float ambient[3] = { dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z };
            if (ImGui::ColorEdit3("ambient", ambient))
            {
                dirLight.ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
            }

            float diffuse[3] = { dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z };
            if (ImGui::ColorEdit3("diffuse", diffuse))
            {
                dirLight.diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
            }

            float specular[3] = { dirLight.specular.x, dirLight.specular.y, dirLight.specular.z };
            if (ImGui::ColorEdit3("specular", specular))
            {
                dirLight.specular = glm::vec3(specular[0], specular[1], specular[2]);
            }

            ImGui::Separator();

            // Simple Point Light Position Control
            ImGui::Text("Point Light Position");
            glm::vec3 pointPos = scene.getLights().getPointLightPosition();
            float pos[3] = { pointPos.x, pointPos.y, pointPos.z };
            if (ImGui::DragFloat3("position", pos, 0.1f, -10.0f, 10.0f, "%.2f"))
            {
                scene.getLights().setPointLightPosition(glm::vec3(pos[0], pos[1], pos[2]));
            }

            ImGui::Separator();

        }
    }

    // ------------------------------------------------------------------
    // camera info
    void EditorPanel::drawCameraInfo(ui::Scene& scene)
    {
        
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
    }

    // ------------------------------------------------------------------
    // performance info
    void EditorPanel::drawPerformanceInfo(ui::Scene& scene)
    {    
        if (!ImGui::CollapsingHeader("Profiler", ImGuiTreeNodeFlags_DefaultOpen))
        {
            return;
        }

        const ImGuiIO& io = ImGui::GetIO();
        float fps = io.Framerate;
        float frameTime = 1.0f / std::max(fps, 0.01f);

		ImGui::PlotHistogram("fps", profilerGraph->fpsHistory.data(), int(profilerGraph->fpsHistory.size()), 0, NULL, 0.0f, 120.0f, ImVec2(200, 80));
		ImGui::PlotHistogram("frametime", profilerGraph->frameTimeHistory.data(), int(profilerGraph->frameTimeHistory.size()), 0, NULL, 0.0f, 50.0f, ImVec2(200, 80));

        // Build fake legit::ProfilerTask stream for one frame
        std::vector<ImGuiUtils::ProfilerTask> tasks;
        tasks.reserve(16);

        auto emitTask = [&](const char* name, uint32_t color, float startMs, float endMs)
        {
            ImGuiUtils::ProfilerTask t; t.name = name; t.color = color; t.startTime = startMs / 1000.0f; t.endTime = endMs / 1000.0f; tasks.push_back(t);
        };

        float t0 = 0.0f;
        auto rnd = [](float a, float b){ return a + (b - a) * (rand() % 100) / 100.0f; };
        float renderMs = rnd(0.1f, 1.1f); if ((rand() % 80) == 0) renderMs += rnd(4.0f, 8.0f);
        float collideMs = rnd(0.2f, 1.2f);
        float particleMs = rnd(0.3f, 1.5f);
        emitTask("Render", IM_COL32( 64,185,255,255), t0, t0 + renderMs); t0 += renderMs;
        emitTask("Collision", IM_COL32(255,170, 64,255), t0, t0 + collideMs); t0 += collideMs;
        emitTask("Particle", IM_COL32( 64,220,120,255), t0, t0 + particleMs); t0 += particleMs;

        profilerGraph->LoadFrameData(tasks.data(), tasks.size());
        profilerGraph->PushPerf(fps, 1000.0f * frameTime);

        int legendWidth = 200;
        ImVec2 canvas = ImGui::GetContentRegionAvail();
        int graphWidth = int(canvas.x) - legendWidth;
        int height = 180;
        profilerGraph->RenderTimings(graphWidth, legendWidth, height, 0, frameTime);
    }

}