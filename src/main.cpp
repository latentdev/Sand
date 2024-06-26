#include <memory>
#include <iostream>
#include "glm/glm.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "Simulator.hpp"
#include "PhysicsEngine.hpp"
#include "IRenderer.hpp"
#include "OpenGLRenderer.hpp"

int main() {
	auto renderer = std::make_unique<renderer::OpenGLRenderer>();
    //auto renderer = std::make_unique<DirectXRenderer>(); // Switch renderer
	if (!renderer->init()) {
		std::cerr << "Failed to initialize renderer" << std::endl;
		return -1;
	}
	auto simulator = std::make_unique<sim::Simulator>(1080, 1080);
	auto physicsEngine = std::make_unique<sim::PhysicsEngine>();

    // Adding particles with random colors
    simulator->addParticle(400, 300, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red particle
    simulator->addParticle(420, 300, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green particle
    simulator->addParticle(440, 300, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); // Blue particle

    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        simulator->update(deltaTime);


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer->render(simulator->getParticles());


        glfwPollEvents();
    }

    renderer->cleanup();
    return 0;

}