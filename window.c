#include "window.h"

int clean_exit(program_t p, int code) {
	if (p.is_glfw) {
		if (p.window != NULL) glfwDestroyWindow(p.window);
		glfwTerminate();
	}
	return code;
}
