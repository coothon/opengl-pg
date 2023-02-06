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

int main (void);

int main(void) {
	program_t *program = (program_t *)calloc(1, sizeof(program_t));
	if (!program) {
		program_log_error("Memory allocation failed. Exiting. . . .");
		return EXIT_FAILURE;
	}

	// Source shaders for triangle renderer.
	if (!(program->render.triangle_r.vert.shader_source = read_file(SS_VERT_PATH))) {
		program_log_error("Unable to find/read \""SS_VERT_PATH"\" file. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}
#ifdef PROGRAM_OPENGL_INFO
	{
		char info_vert[2048] = {0};
		snprintf(info_vert, 2048, "Vertex shader:\n%s", program->render.triangle_r.vert.shader_source);
		program_log_info(info_vert);
	}
#endif
	if (!(program->render.triangle_r.frag.shader_source = read_file(SIMPLE_FRAG_PATH))) {
		program_log_error("Unable to find/read \""SIMPLE_FRAG_PATH"\" file. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}
#ifdef PROGRAM_OPENGL_INFO
	{
		char info_frag[2048] = {0};
		snprintf(info_frag, 2048, "Fragment shader:\n%s", program->render.triangle_r.frag.shader_source);
		program_log_info(info_frag);
	}
#endif

	// Source shaders for background renderer.
	if (!(program->render.background_r.vert.shader_source = read_file(CS_VERT_PATH))) {
		program_log_error("Unable to find/read \""CS_VERT_PATH"\" file. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}
#ifdef PROGRAM_OPENGL_INFO
	{
		char info_vert[2048] = {0};
		snprintf(info_vert, 2048, "Vertex shader:\n%s", program->render.background_r.vert.shader_source);
		program_log_info(info_vert);
	}
#endif
	if (!(program->render.background_r.frag.shader_source = read_file(BACKGROUND_FRAG_PATH))) {
		program_log_error("Unable to find/read \""BACKGROUND_FRAG_PATH"\" file. Exiting. . . .");
		return clean_exit(program, EXIT_FAILURE);
	}
#ifdef PROGRAM_OPENGL_INFO
	{
		char info_frag[2048] = {0};
		snprintf(info_frag, 2048, "Fragment shader:\n%s", program->render.background_r.frag.shader_source);
		program_log_info(info_frag);
	}
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

	// Initialize the triangle renderer.
	populate_renderer_data(&program->render.triangle_r.data, NUM_TRIANGLE_VERTICES, NUM_TRIANGLE_INDICES, triangle_vertices, triangle_indices);
	renderer_init(&program->render.triangle_r);

	// Initialize the background renderer.
	populate_renderer_data(&program->render.background_r.data, NUM_RECT_VERTICES, NUM_RECT_INDICES, rect_vertices, rect_indices);
	renderer_init(&program->render.background_r);

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

		GLfloat uniform_uptime_value = (GLfloat)program->timing.uptime_s;
		GLfloat uniform_uptime_sin_value = (GLfloat)((sin(program->timing.uptime_s) / 2.0) + 0.5);
		GLfloat uniform_vp_width = (GLfloat)callbacks.viewport_width;
		GLfloat uniform_vp_height = (GLfloat)callbacks.viewport_height;
		GLfloat uniform_mousepos_x = (GLfloat)callbacks.mouse_x - (uniform_vp_width / 2.0f);
		GLfloat uniform_mousepos_y = -((GLfloat)callbacks.mouse_y - (uniform_vp_height / 2.0f));

		{ // Background update.
			glUseProgram(program->render.background_r.shader_program);
			glBindVertexArray(program->render.background_r.VAO);
			int uniform_time = glGetUniformLocation(program->render.background_r.shader_program, "uptime");
			int uniform_time_sin = glGetUniformLocation(program->render.background_r.shader_program, "uptime_sin");
			int uniform_resolution = glGetUniformLocation(program->render.background_r.shader_program, "resolution");
			int uniform_mouse = glGetUniformLocation(program->render.background_r.shader_program, "mouse_pos");
			int uniform_scale = glGetUniformLocation(program->render.background_r.shader_program, "scale");
			glUniform1f(uniform_time, uniform_uptime_value);
			glUniform1f(uniform_time_sin, uniform_uptime_sin_value);
			glUniform2f(uniform_resolution, uniform_vp_width, uniform_vp_height);
			glUniform2f(uniform_mouse, uniform_mousepos_x, uniform_mousepos_y);
			glUniform2f(uniform_scale, uniform_uptime_sin_value, 1.0f - uniform_uptime_sin_value);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		{ // Triangle update.
			use_renderer(&program->render.triangle_r);
			int uniform_time = glGetUniformLocation(program->render.triangle_r.shader_program, "uptime");
			int uniform_time_sin = glGetUniformLocation(program->render.triangle_r.shader_program, "uptime_sin");
			int uniform_resolution = glGetUniformLocation(program->render.triangle_r.shader_program, "resolution");
			int uniform_mouse = glGetUniformLocation(program->render.triangle_r.shader_program, "mouse_pos");
			int uniform_offset_pos = glGetUniformLocation(program->render.triangle_r.shader_program, "offset_pos");
			int uniform_scale = glGetUniformLocation(program->render.triangle_r.shader_program, "scale");
			glUniform1f(uniform_time, uniform_uptime_value);
			glUniform1f(uniform_time_sin, uniform_uptime_sin_value);
			glUniform2f(uniform_resolution, uniform_vp_width, uniform_vp_height);
			glUniform2f(uniform_mouse, uniform_mousepos_x, uniform_mousepos_y);
			glUniform2f(uniform_offset_pos, uniform_mousepos_x, uniform_mousepos_y);
			glUniform2f(uniform_scale, 150.0f + 150.0f * uniform_uptime_sin_value, 150.0f + 150.0f * (1.0f - uniform_uptime_sin_value));
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}

		// Prepare your eyes. . . .
		glfwSwapBuffers(program->window);
		glfwPollEvents();
	}

	return clean_exit(program, EXIT_SUCCESS);
}
