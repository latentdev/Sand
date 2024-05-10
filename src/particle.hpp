#ifndef PARTICLE_HPP
#define PARTICLE_HPP

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;

    Particle(sf::Vector2f pos) : position(pos), velocity(sf::Vector2f(0, 0.98)), color(sf::Color::White) {}
};

#endif