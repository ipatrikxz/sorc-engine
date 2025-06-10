#pragma once

struct GLFWwindow;

namespace UI {	
	bool Init(GLFWwindow* window);
	void Update();
	void Pre_Render();
	void Post_Render();
	void Render();

	void SetupDocking();

	void Cleanup();
}