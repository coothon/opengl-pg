#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define GLFW_INCLUDE_NONE
#include "include/glad.h"
#include <GLFW/glfw3.h>

#include <math.h>

#include "include/util.h"
#include "include/render.h"
#include "include/window.h"
#include "include/file.h"

#define GL_MAJ_VER 4
#define GL_MIN_VER 6

int main (void);

int main(void) {
	program_t *program = (program_t *)calloc(1, sizeof(program_t));
	if (!(program->render.RENDERER1.vert.shader_source = read_file(SIMPLE_VERT_PATH))) {
		program_log_error("Unable to find/read \"simple.vert\" file. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}
#ifdef PROGRAM_OPENGL_INFO
	char info_vert[2048] = {0};
	snprintf(info_vert, 2048, "Vertex shader:\n%s", program->render.RENDERER1.vert.shader_source);
	program_log_info(info_vert);
#endif
	if (!(program->render.RENDERER1.frag.shader_source = read_file(SIMPLE_FRAG_PATH))) {
		program_log_error("Unable to find/read \"simple.frag\" file. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}
#ifdef PROGRAM_OPENGL_INFO
	char info_frag[2048] = {0};
	snprintf(info_frag, 2048, "Fragment shader:\n%s", program->render.RENDERER1.frag.shader_source);
	program_log_info(info_frag);
#endif

	// GLFW init.
	if (!(program->is_glfw = glfwInit())) {
		program_log_error("GLFW initialization failed. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}

	glfwSetErrorCallback(glfw_error_cb);
	
	// Window creation config.
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJ_VER);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MIN_VER);
	program->window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE, NULL, NULL);
	if (!program->window) {
		program_log_error("GLFW window Creation failed. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}

	glfwMakeContextCurrent(program->window);

	// GLAD init.
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwGetFramebufferSize(program->window, &program->width, &program->height);
	glViewport(0, 0, program->width, program->height);
	glfwSetFramebufferSizeCallback(program->window, glfw_framebuffer_size_cb);
	glfwSetKeyCallback(program->window, glfw_key_cb);
	glfwSetCursorPosCallback(program->window, glfw_cursorpos_cb);

#ifdef PROGRAM_DEBUG_INFO
	char info_string[512] = {0};
#endif
	double temp_time;
	program->timing.uptime_s = glfwGetTime();

	glfwSwapInterval(0);
	glClearColor(0.3f, 0.3, 0.3, 1.0f);

	populate_renderer_data(&program->render.RENDERER1.data, NUM_TRIANGLE_VERTICES, NUM_TRIANGLE_INDICES, triangle_vertices, triangle_indices);
	renderer_init(&program->render.RENDERER1);

	// Main event loop. This is where everything happens.
	while (!glfwWindowShouldClose(program->window)) {
		temp_time = glfwGetTime();
		calculate_frametime(&program->timing, temp_time);
		calculate_fps(&program->timing);
		program->timing.uptime_s = temp_time;

#ifdef PROGRAM_DEBUG_INFO
		snprintf(info_string, (size_t)512, "Timing data:\nuptime_s: %G\nframetime_ms: %G\nfps: %G",
				 program->timing->uptime_s, program->timing->frametime_ms, program->timing->fps);
		program_log_info(info_string);
#endif

		glClear(GL_COLOR_BUFFER_BIT);
		use_renderer(&program->render.RENDERER1);

		int uniform_time = glGetUniformLocation(program->render.RENDERER1.shader_program, "uptime");
		int uniform_time_sin = glGetUniformLocation(program->render.RENDERER1.shader_program, "uptime_sin");
		int uniform_resolution = glGetUniformLocation(program->render.RENDERER1.shader_program, "resolution");
		int uniform_mouse = glGetUniformLocation(program->render.RENDERER1.shader_program, "mouse_pos");
		glUniform1f(uniform_time, (GLfloat)program->timing.uptime_s);
		glUniform1f(uniform_time_sin, (GLfloat)((sin(program->timing.uptime_s) / 2.0) + 0.5));
		glUniform2f(uniform_resolution, callbacks.viewport_width, callbacks.viewport_height);
		glUniform2f(uniform_mouse, ((GLfloat)callbacks.mouse_x) - callbacks.viewport_width / 2.0f, ((GLfloat)callbacks.mouse_y) - callbacks.viewport_height / 2.0f);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(program->window);
		glfwPollEvents();
	}

	return clean_exit(program, EXIT_SUCCESS);
}
