#pragma once

#include <glm/glm.hpp>

namespace Engine {
	void Run();
}

namespace Game {
	void Init();

	// Update the game state
	void Update();
	void UpdateDeltaTime();
	static float GetDeltaTime();
}
