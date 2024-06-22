#include "PhysicsEngine.hpp"

namespace sim {

    void PhysicsEngine::updatePhysics(Particle& particle, float deltaTime) {
        // Apply gravity
        particle.velocity.y -= gravity * deltaTime;

        // Update particle position based on its velocity
        particle.position += particle.velocity * deltaTime;

        // Apply friction or other forces as needed
        particle.velocity *= friction;
    }

}