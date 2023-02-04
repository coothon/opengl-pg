#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define GLFW_INCLUDE_NONE
#include "include/khrplatform.h"
#include "include/glad.h"
#include <GLFW/glfw3.h>

#include "util.h"
#include "window.h"

#define GL_MAJ_VER 4
#define GL_MIN_VER 6

int main (void);

int main(void) {
	program_t program = {0};

	// GLFW init.
	if ((program.is_glfw = glfwInit()) == GLFW_FALSE) {
		glfw_error_cb(0, "GLFW initialization failed. Exiting. . . .");
		clean_exit(program, EXIT_FAILURE);
	}

	glfwSetErrorCallback(glfw_error_cb);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJ_VER);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MIN_VER);
	program.window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE, NULL, NULL);
	if (program.window == NULL) {
		glfw_error_cb(0, "GLFW window Creation failed. Exiting. . . .");
		clean_exit(program, EXIT_FAILURE);
	}

	glfwMakeContextCurrent(program.window);

	glfwSetKeyCallback(program.window, glfw_key_cb);

	// GLAD init.
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	glfwGetFramebufferSize(program.window, &program.width, &program.height);
	glViewport(0, 0, program.width, program.height);

	glfwSwapInterval(1);

	// Main event loop. This is where everything happens.
	while (!glfwWindowShouldClose(program.window)) {
		program.time = glfwGetTime();

		glfwSwapBuffers(program.window);
		glfwPollEvents();
	}

	return clean_exit(program, EXIT_SUCCESS);
}
