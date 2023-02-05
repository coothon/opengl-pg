#ifndef RENDER_H_
#define RENDER_H_

#include <stdlib.h>
#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>

#include "file.h"
#include "util.h"

// Vertices for test triangle.
static float tt_vertices[] = {
	/* x      y     z    */
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
};

typedef struct {
	char *shader_source;
	unsigned int shader;
	int shader_type;
} shader_t;

typedef struct {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int shader_program;
} renderer;

typedef struct {
	renderer *RENDERER1;
	shader_t *simple_vert;
	shader_t *simple_frag;
} render_t;


int render_init(renderer *, shader_t *, shader_t *);
int shader_init(shader_t *);



#endif // RENDER_H_
