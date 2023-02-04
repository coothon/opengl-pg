#include "util.h"

void glfw_error_cb(int e, const char *desc) {
	fprintf(stderr, "[ERROR] %s\n", desc);
}

void glfw_key_cb(GLFWwindow *w, int key, int scancode, int action, int mods) {
	switch (action) {
	case GLFW_PRESS:
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(w, GLFW_TRUE);
			break;
		default:
			return;
		}
	default:
		return;
	}
}
