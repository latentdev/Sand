#include "Simulator.hpp"

namespace sim {

    sim::Simulator::Simulator(int width, int height) : width(width), height(height) {}

    void Simulator::update(float deltaTime) {
        for (auto& particle : particles) {
            if (particle.isActive) {
                // Update particle position based on its velocity
                physicsEngine.updatePhysics(particle, deltaTime);

                // Boundary check and handle collisions with the ground
                if (particle.position.y < 0.0f) {
                    particle.position.y = 0.0f;
                    particle.velocity.y = 0.0f; // Stop the particle on the ground
                }
            }
        }
    }

    void Simulator::addParticle(float x, float y, const glm::vec4& color) {
        particles.emplace_back(glm::vec2(x, y), glm::vec2(0.0f, 0.0f), color, true);
    }

}