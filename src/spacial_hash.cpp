#include "spacial_hash.hpp"
#include "particle.hpp"


class SpatialHash {
private:
    std::unordered_map<int, std::vector<Particle*>> map;
    int cellSize;
    int width;

    int hash(const sf::Vector2f& position) {
        int x = position.x / cellSize;
        int y = position.y / cellSize;
        return x + y * width; // Simple hash function
    }

public:
    SpatialHash(int cellSize, int width) : cellSize(cellSize), width(width) {}

    void insert(Particle* particle) {
        int cellHash = hash(particle->position);
        map[cellHash].push_back(particle);
    }

    void move(Particle* particle, const sf::Vector2f& newPosition) {
        int oldHash = hash(particle->position);
        int newHash = hash(newPosition);

        if (oldHash != newHash) {
            // Remove from the old cell
            auto& vec = map[oldHash];
            vec.erase(std::remove(vec.begin(), vec.end(), particle), vec.end());

            // Add to the new cell
            map[newHash].push_back(particle);
        }

        // Update position
        particle->position = newPosition;
    }

    std::vector<Particle*> getNearby(const sf::Vector2f& position) {
        int cellHash = hash(position);
        return map[cellHash]; // Return a copy of the list of particles in the same cell
    }
};