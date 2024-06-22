#pragma once

#include <vector>
#include <unordered_map>

#include "particle.hpp"

class SpacialHash {
private:
	std::unordered_map<int, std::vector<Particle*>> map;
	int cellSize;
	int width;

	int hash(const glm::vec2& position);

public:
	SpacialHash(int cellSize, int width);
	void insert(Particle* particle);
	void move(Particle* particle, const glm::vec2& newPosition);
	std::vector<Particle*> getNearby(const glm::vec2& position);
};
