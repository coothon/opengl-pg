#ifndef RENDER_H_
#define RENDER_H_

#include <stdlib.h>
#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>

#include "file.h"
#include "util.h"

typedef struct {
	GLchar *shader_source; // FREE
	GLuint shader;
	GLint shader_type;
} shader_t;

typedef struct {
	vec2_f position;
	vec3_f color;
	vec2_f tex_coords;
} vertex_t;

typedef struct {
	vertex_t *vertices; // FREE
	GLuint *indices; // FREE
	GLint num_vertices;
	GLint num_indices;
} renderer_data;

typedef struct {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	shader_t vert;
	shader_t frag;
	GLuint shader_program;
	renderer_data data;
} renderer_t;

typedef struct {
	renderer_t RENDERER1;
} render_t;

#define NUM_TRIANGLE_VERTICES 3
static vertex_t triangle_vertices[] = {
	{-0.5f, -0.5f,
	1.0f, 0.0f, 0.0f,
	-1.0f, -1.0f},
	{0.5f, -0.5f,
	0.0f, 1.0f, 0.0f,
	1.0f, -1.0f},
	{0.0f, 0.5f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f}
};

#define NUM_TRIANGLE_INDICES 3
static GLuint triangle_indices[] = {
	0, 1, 2
};

void populate_renderer_data(renderer_data *, GLint, GLint, vertex_t *, GLuint *);
int renderer_init(renderer_t *);
int shader_init(shader_t *);
void use_renderer(renderer_t *);

#endif // RENDER_H_