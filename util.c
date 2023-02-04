#include "include/util.h"

void glfw_error_cb(int e, const char *desc) {
	program_log_error(desc);
}

void glfw_key_cb(GLFWwindow *w, int key, int scancode, int action, int mods) {
#ifdef PROGRAM_DEBUG_INFO
	char info_string[512] = {0};
#endif

	switch (action) {
	case GLFW_PRESS:
#ifdef PROGRAM_DEBUG_INFO
		snprintf(info_string, (size_t)512, "Key %s pressed.", glfwGetKeyName(key, 0));
		program_log_info(info_string);
#endif
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

void glfw_framebuffer_size_cb(GLFWwindow *w, int width, int height) {
#ifdef PROGRAM_DEBUG_INFO
	char info_string[512] = {0};
	snprintf(info_string, (size_t)512, "New OpenGL framebuffer size: (x: %i, y: %i).", width, height);
	program_log_info(info_string);
#endif
	glViewport(0, 0, width, height);
}

#ifdef PROGRAM_DEBUG_INFO
void glfw_cursorpos_cb(GLFWwindow *w, double x, double y) {
	char info_string[512] = {0};
	snprintf(info_string, (size_t)512, "New cursor position: (x: %G, y: %G).", x, y);
	program_log_info(info_string);
}
#endif

void calculate_frametime(timing_t *t, double curr) {
	t->frametime_s = (curr - t->uptime_s);
	t->frametime_ms = t->frametime_s * 1000.0d;
}

void calculate_fps(timing_t *t) {
	t->fps = 1.0d / t->frametime_s;
}

void program_log_error(const char *log) {
	fprintf(stderr, "[ERROR] %s\n", log);
}

void program_log_warn(const char *log) {
	fprintf(stdout, "[WARN] %s\n", log);
}

void program_log_info(const char *log) {
	fprintf(stdout, "[INFO] %s\n", log);
}
