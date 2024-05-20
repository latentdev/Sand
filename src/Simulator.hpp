#pragma once
#include <vector>
#include "Particle.hpp"

class Simulator {
public:
    Simulator(int width, int height);
    void update(float deltaTime);
    void addParticle(float x, float y, const glm::vec4& color);
    const std::vector<Particle>& getParticles() const { return particles; }

private:
    int width, height;
    std::vector<Particle> particles;
	PhysicsEngine physicsEngine;
};