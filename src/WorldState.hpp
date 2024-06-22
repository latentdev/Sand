#pragma once

#include <vector>
#include "Particle.hpp"

class WorldState {
private:
	int height;
	int width;
	float gravity;
	std::vector<Particle> particles;
	
	void applyPhysics(Particle& p, float deltaTime);
	void resolveCollisions(Particle& p1, Particle& p2);

public:
	WorldState(int height, int width, float gravity);
	void update();
};