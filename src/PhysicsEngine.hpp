#pragma once
#include <vector>
#include "Particle.hpp"

class PhysicsEngine {
public:
    void update(std::vector<Particle>& particles, float deltaTime, int width, int height);
};