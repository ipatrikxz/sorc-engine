#include "Engine.h"

#include <glad/glad.h>
#include <string>

int main() 
{
	std::unique_ptr<app::Engine> engine;
	engine = std::make_unique<app::Engine>();
	engine->run();
	return 0;
}
