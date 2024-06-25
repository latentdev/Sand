#pragma once
#include "Particle.hpp"
#include "IRenderer.hpp"

class OpenGLRenderer : public IRenderer {
public:
    void init() override;
    void render(const std::vector<Particle>& particles) override;
    void cleanup() override;
private:
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
};