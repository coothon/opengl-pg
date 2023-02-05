#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdlib.h>
#include <stdbool.h>
#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>

#include "util.h"
#include "render.h"

#define WINDOW_TITLE "OpenGL Playground"
#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

typedef struct {
	int width, height;
	bool is_glfw;
	GLFWwindow *window;
	double cursor_x, cursor_y;
	timing_t *timing;
	render_t *render;
} program_t;

int clean_exit(program_t *, int);

#endif // WINDOW_H_
