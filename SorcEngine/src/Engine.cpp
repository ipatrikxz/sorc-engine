
#include "Engine.h"

#include "Core/GL.h"
#include "Core/Input.h"
#include "Util.hpp"
#include "Renderer/Renderer.h"

/*
*	Game
*
*	Contains game-specific logic, such as camera movement based on keyboard input.
*/
namespace Game {

	Transform _camera;
	float _camSpeed = 0.05f;

	void Init() {
		_camera.position = glm::vec3(3.75f, 5.0f, 10.3f);
		_camera.rotation = glm::vec3(-1.0f, 0.0f, 0.0f);
	}

	void Update() {

		if (Input::KeyPressed(GLFW_KEY_ESCAPE)) {
			GL::SetWindowShouldClose(true);
		}

		if (Input::KeyDown(GLFW_KEY_A)) {
			_camera.position.x -= _camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_D)) {
			_camera.position.x += _camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_W)) {
			_camera.position.z -= _camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_S)) {
			_camera.position.z += _camSpeed;
		}
	}

	glm::mat4 GetViewMatrix() {
		return glm::inverse(_camera.to_mat4());
	}
}

void Engine::Run()
{
	std::cout << "You are you're own worst enemy.\n";
	std::cout << "Failure is an illusion.\n";
	std::cout << "Accept no inpass.\n";

	GL::Init(1280, 720, "SorcEngine");
	Game::Init();
	Renderer::Init();

	while (GL::WindowIsOpen()) {
		Input::Update();
		Game::Update();
		Renderer::RenderFrame(Game::GetViewMatrix());
		GL::SwapBuffersPollEvents();
	}

	GL::Cleanup();
	return;
}

