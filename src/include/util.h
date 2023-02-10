#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>


// Specify OpenGL version to use; it will use the closest match.
// Currently it is set to 4.6, the newest.
#define GL_MAJ_VER 4
#define GL_MIN_VER 6

// These control console output.
#define PROGRAM_DEBUG_INFO 1
#define PROGRAM_OPENGL_INFO 1

typedef struct {
	GLfloat x, y;
} vec2_f;

typedef struct {
	GLfloat x, y, z;
} vec3_f;

typedef struct {
	GLfloat x, y, z, w;
} vec4_f;

typedef struct {
	GLuint x, y;
} vec2_ui;

typedef struct {
	GLuint x, y, z;
} vec3_ui;

typedef struct {
	GLuint x, y, z, w;
} vec4_ui;

typedef struct {
	double uptime_s;
	double frametime_s;
	double frametime_ms;
	double fps;
} timing_t;


typedef struct {
	GLint viewport_width;
	GLint viewport_height;
	GLdouble mouse_x;
	GLdouble mouse_y;
} global_data;

// Scary!
extern global_data callbacks;

void glfw_error_cb(int, const char *);
void glfw_key_cb(GLFWwindow *, int, int, int, int);
void glfw_framebuffer_size_cb(GLFWwindow *, int, int);
void glfw_cursorpos_cb(GLFWwindow *, double, double);
void calculate_frametime(timing_t *, double);
void calculate_fps(timing_t *);
void program_log_error(const char *);
void program_log_warn(const char *);
void program_log_info(const char *);


#endif // UTIL_H_
