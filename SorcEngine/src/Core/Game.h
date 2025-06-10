#pragma once

#include "Player.h"
#include "Renderer/Renderer.h"

namespace Game
{
	Player* player;

	float deltaTime;
	float lastFrame;
	float currentFrame;

	void Init()
	{
		player = new Player();
		player->Init();

		deltaTime = 0.0f;
		lastFrame = static_cast<float>(glfwGetTime());

		std::cout << "Game initialized.\n";
	}

	void Update() {
		UpdateDeltaTime();

		if (player)
		{
			player->Update(deltaTime);
			Renderer::RenderFrame(player->GetViewMatrix());
		}
	}

	void UpdateDeltaTime() {
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	static float GetDeltaTime() {
		return deltaTime;
	}

	static Player* GetPlayer() {
		return player;
	}
}