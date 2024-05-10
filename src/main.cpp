#include <SFML/Graphics.hpp>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;

    Particle(sf::Vector2f pos) : position(pos), velocity(sf::Vector2f(0, 0.1)), color(sf::Color::White) {}
};

void update(std::vector<Particle>& particles) {
    for (auto& p : particles) {
        // Apply gravity
        p.position += p.velocity;

        // Simple ground collision
        if (p.position.y > 600) { // Assuming the window height is 600
            p.position.y = 600;
            p.velocity.y = 0;
        }
    }
}

void render(sf::RenderWindow& window, const std::vector<Particle>& particles) {
    window.clear();
    for (const auto& p : particles) {
        sf::CircleShape shape(2); // Radius of 2 pixels
        shape.setPosition(p.position);
        shape.setFillColor(p.color);
        window.draw(shape);
    }
    window.display();
}

void handleEvents(sf::RenderWindow& window, std::vector<Particle>& particles) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            // Add a particle where the mouse was clicked
            particles.push_back(Particle(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)));
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Falling Sand Simulation");
    std::vector<Particle> particles;

    while (window.isOpen()) {
        handleEvents(window, particles);
        update(particles);
        render(window, particles);
    }

    return 0;
}