#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>

//#define PROGRAM_DEBUG_INFO
#define PROGRAM_OPENGL_INFO

typedef struct {
	double uptime_s, frametime_s, frametime_ms, fps;
} timing_t;


void glfw_error_cb(int, const char *);
void glfw_key_cb(GLFWwindow *, int, int, int, int);
void glfw_framebuffer_size_cb(GLFWwindow *, int, int);
#ifdef PROGRAM_DEBUG_INFO
void glfw_cursorpos_cb(GLFWwindow *, double, double);
#endif
void calculate_frametime(timing_t *, double);
void calculate_fps(timing_t *);
void program_log_error(const char *);
void program_log_warn(const char *);
void program_log_info(const char *);


#endif // UTIL_H_
