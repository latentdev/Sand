#pragma once
#include <vector>
#include "Particle.hpp"

namespace sim {

	class PhysicsEngine {
	public:
		void updatePhysics(Particle& particle, float deltaTime);
	private:
		float gravity = 9.81f;
		float friction = 0.98f;
	};
}