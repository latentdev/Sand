#ifndef PARTICLE_HPP
#define PARTICLE_HPP

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float mass;
    float friction;

    Particle(sf::Vector2f pos, float m, float f) : position(pos), velocity(sf::Vector2f(0, 0)), mass(m), friction(f), color(sf::Color::White) {}
};

#endif