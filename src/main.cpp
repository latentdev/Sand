#include <memory>
#include <glm/glm.hpp>
#include "Simulator.hpp"
#include "PhysicsEngine.hpp"
#include "IRenderer.hpp"
#include "OpenGLRenderer.hpp"
// #include "DirectXRenderer.h" // Include other renderers as needed

int main() {
    std::unique_ptr<IRenderer> renderer = std::make_unique<OpenGLRenderer>();
    // std::unique_ptr<IRenderer> renderer = astd::make_unique<DirectXRenderer>(); // Switch renderer

    renderer->init();

    Simulator simulator(800, 600);
    PhysicsEngine physicsEngine;

    // Adding particles with random colors
    simulator.addParticle(400, 300, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red particle
    simulator.addParticle(420, 300, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green particle
    simulator.addParticle(440, 300, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); // Blue particle

    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        simulator.update(deltaTime);
        physicsEngine.update(simulator.getParticles(), deltaTime, 800, 600);

        renderer->render(simulator.getParticles());

        glfwPollEvents();
    }

    renderer->cleanup();
    return 0;
}

// #include <SFML/Graphics.hpp>
// #include <format>
// #include <iostream>
// #include <string>
// #include "particle.hpp"



// void update(std::vector<Particle>& particles) {
//     for (auto& p : particles) {
//         // Apply gravity
//         p.position += p.velocity;

//         // Simple ground collision
//         if (p.position.y > 1080) { // Assuming the window height is 600
//             p.position.y = 1080;
//             p.velocity.y = 0;
//             std::cout << std::format("Particle has stopped at ({},{})", p.position.x, p.position.y) << std::endl;
//         }
//     }
// }

// void render(sf::RenderWindow& window, const std::vector<Particle>& particles) {
//     window.clear();
//     for (const auto& p : particles) {
//         sf::CircleShape shape(2); // Radius of 2 pixels
//         shape.setPosition(p.position);
//         shape.setFillColor(p.color);
//         window.draw(shape);
//     }
//     window.display();
// }

// void handleEvents(sf::RenderWindow& window, std::vector<Particle>& particles) {
//     sf::Event event;
//     while (window.pollEvent(event)) {
//         if (event.type == sf::Event::Closed)
//             window.close();
//         if (event.type == sf::Event::MouseButtonPressed) {
//             // Add a particle where the mouse was clicked
//             particles.push_back(Particle(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), 1, 1));
//         }
//     }
// }

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(1080, 1080), "Falling Sand Simulation");
//     std::vector<Particle> particles;

//     while (window.isOpen()) {
//         handleEvents(window, particles);
//         update(particles);
//         render(window, particles);
//     }

//     return 0;
// }