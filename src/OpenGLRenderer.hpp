#pragma once
#include "glm/glm.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "Particle.hpp"
#include "IRenderer.hpp"


namespace renderer {

    class OpenGLRenderer : public IRenderer {
    public:
        bool init() override;
        void render(const std::vector<Particle>& particles) override;
        void cleanup() override;
    private:
        glm::vec2 mapToOpenGLCoordinates(glm::vec2 position, int windowWidth, int windowHeight);
        GLFWmonitor* getRadialDisplayMonitor();
        unsigned int compileShader(unsigned int type, const char* source);
        unsigned int createShaderProgram();

		GLFWwindow* window;
        const char* vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec2 aPos;
            layout (location = 1) in vec4 aColor;

            out vec4 color;

            void main()
            {
                gl_Position = vec4(aPos, 0.0, 1.0);
                color = aColor;
            }
            )";

        // Fragment shader source code
        const char* fragmentShaderSource = R"(
            #version 330 core
            in vec4 color;

            out vec4 FragColor;

            void main()
            {
                FragColor = color;
            }
            )";

        unsigned int shaderProgram = 0;
    };
}