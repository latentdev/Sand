#include "world_state.hpp"

void WorldState::applyPhysics(Particle& p, float deltaTime) {
	//// Calculate new velocity until terminal velocity is reached
	//if (p.velocity.y < 1) {
	//	p.velocity.y += gravity;
	//}

	//p.position += p.velocity;

	//// Simple ground collision
	//if (p.position.y > height) {
	//	p.position.y = height;
	//	p.velocity.y = 0;
	//}
	p.velocity.y += gravity * p.mass * deltaTime; //apply gravity
	p.velocity.y *= (1 - p.friction); //apply friction
}

WorldState::WorldState(int height, int width, float gravity) {
	this->height = height;
	this->width = width;
	this->gravity = gravity;
}

void WorldState::update() {
	for (auto& p : particles) {
		// Calculate new velocity until terminal velocity is reached
		if (p.velocity.y < 1) {
			p.velocity.y += gravity;
		}

		p.position += p.velocity;

		// Simple ground collision
		if (p.position.y > height) {
			p.position.y = height;
			p.velocity.y = 0;
		}
	}
}