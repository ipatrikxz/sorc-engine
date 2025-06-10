#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Resolutions {
    glm::vec2 gBuffer;
    glm::vec2 finalImage;
    glm::vec2 ui;
};

namespace Config {
    void Init();
    const Resolutions& GetResolutions();
}