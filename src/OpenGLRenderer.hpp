#pragma once
#include "Particle.hpp"
#include "IRenderer.hpp"

class OpenGLRenderer : public IRenderer {
public:
    void init() override;
    void render(const std::vector<Particle>& particles) override;
    void cleanup() override;
};