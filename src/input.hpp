#include "GLFW/glfw3.h"

namespace input {
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void processInput(GLFWwindow* window);
}