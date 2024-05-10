#ifndef SPACIAL_HASH_HPP
#define SPACIAL_HASH_HPP

#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "particle.h"

class SpacialHash {
private:
	std::unordered_map<int, std::vector<Particle*>> map;
	int cellSize;
	int width;

	int hash(const sf::Vector2f& position);

public:
	SpacialHash(int cellSize, int width);
	void insert(Particle* particle);
	void move(Particle* particle, const sf::Vector2f& newPosition);
	std::vector<Particle*> getNearby(const sf::Vector2f& position, float radius);
	void clear();
};

#endif
