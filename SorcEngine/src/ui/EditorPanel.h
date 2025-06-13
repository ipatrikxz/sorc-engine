#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>

#include "imgui.h"
#include <imfilebrowser.h>

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

			shaderColor = glm::vec3(1, 1, 1);
		}

		void render(ui::Scene& scene);
		void setMeshLoadCallback(const std::function<void(std::string)> callback)
		{
			meshLoadCallback = callback;
		}

	private:
		// create a file browser instance
		ImGui::FileBrowser fileDialog;

		std::function<void(const std::string&)> meshLoadCallback;

		std::string currentFile;

		glm::vec3 shaderColor;

	};
}