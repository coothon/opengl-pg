#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdbool.h>
#define GLFW_INCLUDE_NONE
#include "include/khrplatform.h"
#include "include/glad.h"
#include <GLFW/glfw3.h>


#define WINDOW_TITLE "OpenGL Playground"
#define WINDOW_SIZE_X 640
#define WINDOW_SIZE_Y 480
typedef struct {
	int width, height;
	double time;
	bool is_glfw;
	bool is_glew;
	GLFWwindow *window;
} program_t;

int clean_exit(program_t, int);

#endif // WINDOW_H_
