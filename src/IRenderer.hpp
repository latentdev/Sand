#pragma once
#include <vector>
#include "Particle.hpp"

class IRenderer {
public:
    virtual void init() = 0;
    virtual void render(const std::vector<Particle>& particles) = 0;
    virtual void cleanup() = 0;
    virtual ~IRenderer() = default;
};