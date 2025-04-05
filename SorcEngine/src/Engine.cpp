
#include "Engine.h"
#include "Core/GL.h"
#include "Core/Input.h"
#include "Util.hpp"
#include "Renderer/Renderer.h"
#include "Core/Player.h"

namespace Engine 
{
	void Run()
	{
		std::cout << "You are you're own worst enemy.\n";
		std::cout << "Failure is an illusion.\n";

		GL::Init(1280, 720, "SorcEngine");
		Game::Init();
		Renderer::Init();


		while (GL::WindowIsOpen()) {
			Game::Update();

			GL::SwapBuffersPollEvents();
		}

		GL::Cleanup();
		return;
	}
}

namespace Game 
{
	float deltaTime;
	float lastFrame;
	float currentFrame;

	Player* player;

	void Init() 
	{
		player = new Player();
	}

	void Update() {
		UpdateDeltaTime();

		if (player)
		{
			player->Update(deltaTime);
		}

		Renderer::RenderFrame(player->GetViewMatrix());
	}

	void UpdateDeltaTime() {
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	static float GetDeltaTime() {
		return deltaTime;
	}

}



