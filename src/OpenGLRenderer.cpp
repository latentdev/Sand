#include "OpenGLRenderer.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"


void OpenGLRenderer::init() {
    if (!glfwInit()) {
        // Handle initialization failure
    }
    GLFWwindow* window = glfwCreateWindow(800, 600, "Sand Simulator", NULL, NULL);
    if (!window) {
        glfwTerminate();
        // Handle window creation failure
    }
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    // Set up OpenGL state
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::render(const std::vector<Particle>& particles) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Render particles
	glDrawArrays(GL_POINTS, 0, particles.size());

    //glBegin(GL_POINTS);
    //for (const auto& particle : particles) {
    //    if (particle.isActive) {
    //        glColor4f(particle.color.r, particle.color.g, particle.color.b, particle.color.a);
    //        glVertex2f(particle.position.x, particle.position.y);
    //    }
    //}
    //glEnd();
    glfwSwapBuffers(glfwGetCurrentContext());
}

void OpenGLRenderer::cleanup() {
    glfwTerminate();
}