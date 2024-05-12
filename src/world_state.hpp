#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "particle.hpp"

class WorldState {
private:
	int height;
	int width;
	float gravity;
	std::vector<Particle> particles;
	
	void applyPhysics(Particle& p);
	void resolveCollisions(Particle& p1, Particle& p2);

public:
	WorldState(int height, int width, float gravity);
	void update();
};

#endif