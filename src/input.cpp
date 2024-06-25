#include "GLFW/glfw3.h"

namespace input {
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
        }
}