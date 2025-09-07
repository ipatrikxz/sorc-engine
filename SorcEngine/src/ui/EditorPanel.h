#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>
#include <memory>

#include "imgui.h"
#include <imfilebrowser.h>
#include "ProfilerTimeline.h"

namespace ui
{
	class Scene;

	class EditorPanel
	{

	public:
		EditorPanel()
		{
			currentFile = "< ... >";

			fileDialog.SetTitle("File import dialog window");
			fileDialog.SetTypeFilters({ ".obj", ".fbx" });
			fileDialog.SetDirectory("res/models/");

			currentTextureFile = "< ... >";
			textureFileDialog.SetTitle("Texture import dialog window");
			textureFileDialog.SetTypeFilters({ ".png", ".jpg", ".jpeg" });
			textureFileDialog.SetDirectory("res/textures/");

			shaderColor = glm::vec3(1, 1, 1);
			profilerGraph = std::make_unique<ImGuiUtils::ProfilerTimeline>(300);
		}

		void render(ui::Scene& scene);
		void setMeshLoadCallback(const std::function<void(std::string)> callback)
		{
			meshLoadCallback = callback;
		}

		void setTextureLoadCallback(const std::function<void(std::string)> callback)
		{
			textureLoadCallback = callback;
		}

	private:

		void drawMeshControls(ui::Scene& scene);
		void drawLightControls(ui::Scene& scene);
		void drawCameraInfo(ui::Scene& scene);
		void drawPerformanceInfo(ui::Scene& scene);

		// create a file browser instance
		ImGui::FileBrowser fileDialog;
		ImGui::FileBrowser textureFileDialog;

		std::function<void(const std::string&)> meshLoadCallback;
		std::function<void(const std::string&)> textureLoadCallback;

		std::string currentFile;
		std::string currentTextureFile;

		glm::vec3 shaderColor;

		// LegitProfiler-style renderer
		std::unique_ptr<ImGuiUtils::ProfilerTimeline> profilerGraph;

	};
}