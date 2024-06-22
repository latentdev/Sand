#include "SpacialHash.hpp"
#include "particle.hpp"


class SpatialHash {
private:
    std::unordered_map<int, std::vector<Particle*>> map;
    int cellSize;
    int width;

    int hash(const glm::vec2& position) {
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

    void move(Particle* particle, const glm::vec2& newPosition) {
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

    std::vector<Particle*> getNearby(const glm::vec2& position) {
        std::vector<Particle*> nearbyParticles;

        // We'll check this cell and its neighbors
        int baseX = (int)(position.x / cellSize);
        int baseY = (int)(position.y / cellSize);
    
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int x = baseX + dx;
                int y = baseY + dy;
                int cellHash = x + y * width;

                auto it = map.find(cellHash);
                if (it != map.end()) {
                    nearbyParticles.insert(nearbyParticles.end(), it->second.begin(), it->second.end());
                }
            }
        }

        return nearbyParticles;
    }
};