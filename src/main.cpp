#include <memory>
#include <iostream>
#include "glm/glm.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "Simulator.hpp"
#include "PhysicsEngine.hpp"
#include "IRenderer.hpp"
#include "OpenGLRenderer.hpp"


// Vertex shader source code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
)";

// Fragment shader source code
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec4 inputColor;
void main()
{
    FragColor = inputColor; // Red color
}
)";

unsigned int shaderProgram;
int colorLocation;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Mouse clicked at (" << xpos << ", " << ypos << ")" << std::endl;
        // Convert screen coordinates to OpenGL coordinates
        //int width, height;
        //glfwGetWindowSize(window, &width, &height);
        //xpos = xpos / width * 2.0 - 1.0;
        //ypos = -ypos / height * 2.0 + 1.0;

		//std::cout << "Converted coordinates at (" << xpos << ", " << ypos << ")" << std::endl;

        float vertices[] = {
            (float)xpos, (float)ypos
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 1);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}

//unsigned int compileShader(unsigned int type, const char* source) {
//    unsigned int shader = glCreateShader(type);
//    glShaderSource(shader, 1, &source, NULL);
//    glCompileShader(shader);
//
//    int success;
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        char infoLog[512];
//        glGetShaderInfoLog(shader, 512, NULL, infoLog);
//        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//    return shader;
//}
//
//unsigned int createShaderProgram() {
//	std::cout << "Compiling shaders..." << std::endl;
//    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
//	std::cout << "Vertex shader compiled successfully" << std::endl;
//    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
//	std::cout << "Fragment shader compiled successfully" << std::endl;
//	std::cout << "Shaders compiled successfully" << std::endl;
//    unsigned int program = glCreateProgram();
//    glAttachShader(program, vertexShader);
//    glAttachShader(program, fragmentShader);
//    glLinkProgram(program);
//
//    int success;
//    glGetProgramiv(program, GL_LINK_STATUS, &success);
//    if (!success) {
//        char infoLog[512];
//        glGetProgramInfoLog(program, 512, NULL, infoLog);
//        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    return program;
//}

//GLFWmonitor* getRadialDisplayMonitor() {
//	int count;
//	GLFWmonitor** monitors = glfwGetMonitors(&count);
//	for (int i = 0; i < count; i++) {
//		//auto name = glfwGetMonitorName(monitors[i]);
//		int xPos, yPos, width, height;
//		glfwGetMonitorWorkarea(monitors[i], &xPos, &yPos, &width, &height);
//		if (width==1080) {
//			return monitors[i];
//		}
//	}
//	return nullptr;
//}
//
//void render(const std::vector<Particle>& particles) {
//    std::vector<float> vertices;
//    for (const auto& particle : particles) {
//        if (particle.isActive) {
//            vertices.push_back(particle.position.x);
//            vertices.push_back(particle.position.y);
//            vertices.push_back(particle.color.r);
//            vertices.push_back(particle.color.g);
//            vertices.push_back(particle.color.b);
//            vertices.push_back(particle.color.a);
//        }
//    }
//
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    glUseProgram(shaderProgram);
//    glPointSize(10.0f);
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_POINTS, 0, vertices.size() / 6);
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto monitor = getRadialDisplayMonitor();
    GLFWwindow* window = glfwCreateWindow(1080, 1080, "Drawable Canvas", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1080, 1080);

    // Compile and link shaders
    shaderProgram = createShaderProgram();

    // Get the location of the uniform variable
    colorLocation = glGetUniformLocation(shaderProgram, "inputColor");

    // Register mouse callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //render

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// #include "DirectXRenderer.h" // Include other renderers as needed
//
//int main() {
//    std::unique_ptr<IRenderer> renderer = std::make_unique<OpenGLRenderer>();
//    // std::unique_ptr<IRenderer> renderer = std::make_unique<DirectXRenderer>(); // Switch renderer
//
//    renderer->init();
//
//    sim::Simulator simulator(800, 600);
//    sim::PhysicsEngine physicsEngine;
//
//    // Adding particles with random colors
//    simulator.addParticle(400, 300, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red particle
//    simulator.addParticle(420, 300, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green particle
//    simulator.addParticle(440, 300, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); // Blue particle
//
//    float lastTime = glfwGetTime();
//    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
//        float currentTime = glfwGetTime();
//        float deltaTime = currentTime - lastTime;
//        lastTime = currentTime;
//
//        simulator.update(deltaTime);
//
//        renderer->render(simulator.getParticles());
//
//        glfwPollEvents();
//    }
//
//    renderer->cleanup();
//    return 0;
//}

