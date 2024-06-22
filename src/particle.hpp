#pragma once

#include "glm/glm.hpp"

struct Particle {
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec4 color;
    float mass;
    float friction;
    bool isActive;

    Particle(const glm::vec2& pos, const glm::vec2& vel, const glm::vec4& col, bool active)
        : position(pos), velocity(vel), color(col), isActive(active) {}
};