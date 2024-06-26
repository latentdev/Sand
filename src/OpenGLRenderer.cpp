#include <iostream>
#include "glm/glm.hpp"
#include "OpenGLRenderer.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace renderer {

    bool OpenGLRenderer::init() {
        if (!glfwInit()) {
            // Handle initialization failure
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		auto monitor = getRadialDisplayMonitor();
        window = glfwCreateWindow(1080, 1080, "Sand Simulator", monitor, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGL(glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        glViewport(0, 0, 1080, 1080);

        // Compile and link shaders
        shaderProgram = createShaderProgram();
        return true;
    }

    glm::vec2 OpenGLRenderer::mapToOpenGLCoordinates(glm::vec2 position, int windowWidth, int windowHeight) {
		float x = (position.x / windowWidth) * 2 - 1;
		float y = (position.y / windowHeight) * 2 - 1;
		return glm::vec2(x, y);
	}

    void OpenGLRenderer::render(const std::vector<Particle>& particles) {
        std::vector<float> vertices;
        std::cout << "Rendering " << particles.size() << " particles" << std::endl;
        for (const auto& particle : particles) {
            if (particle.isActive) {
                int windowWidth, windowHeight;
                glfwGetWindowSize(window, &windowWidth, &windowHeight);
                glm::vec2 mappedPos = mapToOpenGLCoordinates(particle.position, windowWidth, windowHeight);
                std::cout << "Rendering particle at (" << particle.position.x << ", " << particle.position.y << ")" << std::endl;
                std::cout << "Mapped position: (" << mappedPos.x << ", " << mappedPos.y << ")" << std::endl;
                vertices.push_back(mappedPos.x);
                vertices.push_back(mappedPos.y);
                vertices.push_back(particle.color.r);
                vertices.push_back(particle.color.g);
                vertices.push_back(particle.color.b);
                vertices.push_back(particle.color.a);
            }
        }

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glUseProgram(shaderProgram);
        // Set the polygon mode to GL_POINT to ensure points are rendered correctly
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

        // Set the point size
        glPointSize(4.0f);
        // Draw the points
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, vertices.size() / 6);
        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwSwapBuffers(window);
    }

    void OpenGLRenderer::cleanup() {
        glfwTerminate();
    }

    unsigned int OpenGLRenderer::compileShader(unsigned int type, const char* source) {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return shader;
    }

    unsigned int OpenGLRenderer::createShaderProgram() {
        std::cout << "Compiling shaders..." << std::endl;
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        std::cout << "Vertex shader compiled successfully" << std::endl;
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        std::cout << "Fragment shader compiled successfully" << std::endl;
        std::cout << "Shaders compiled successfully" << std::endl;
        unsigned int program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

    GLFWmonitor* OpenGLRenderer::getRadialDisplayMonitor() {
        int count;
        GLFWmonitor** monitors = glfwGetMonitors(&count);
        for (int i = 0; i < count; i++) {
            //auto name = glfwGetMonitorName(monitors[i]);
            int xPos, yPos, width, height;
            glfwGetMonitorWorkarea(monitors[i], &xPos, &yPos, &width, &height);
            if (width == 1080) {
                return monitors[i];
            }
        }
        return nullptr;
    }

}