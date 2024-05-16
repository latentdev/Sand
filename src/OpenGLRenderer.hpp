#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Particle.hpp"
#include "IRenderer.hpp"

class OpenGLRenderer : public IRenderer {
public:
    void init() override;
    void render(const std::vector<Particle>& particles) override;
    void cleanup() override;
};