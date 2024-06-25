#pragma once
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
        GLFWmonitor* getRadialDisplayMonitor();
        unsigned int compileShader(unsigned int type, const char* source);
        unsigned int createShaderProgram();

		GLFWwindow* window;
        const char* vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec2 aPos;
            layout (location = 1) in vec4 aColor;

            out vec4 ourColor;

            void main()
            {
                gl_Position = vec4(aPos, 0.0, 1.0);
                ourColor = aColor;
            }
            )";

        // Fragment shader source code
        const char* fragmentShaderSource = R"(
            #version 330 core
            in vec4 ourColor;

            out vec4 FragColor;

            void main()
            {
                FragColor = ourColor;
            }
            )";

        unsigned int shaderProgram = 0;
    };
}