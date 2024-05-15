#ifndef PARTICLE_HPP
#define PARTICLE_HPP

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float mass;
    float friction;

    Particle(sf::Vector2f pos, float mass, float friction) : position(pos), velocity(sf::Vector2f(0, 0)), mass(mass), friction(friction), color(sf::Color::White) {}
};

#endif