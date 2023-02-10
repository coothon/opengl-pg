#include "include/render.h"
#include "include/glad.h"

// VERTICES AND INDICES MUST BE ALLOCATED ON THE HEAP AND LEFT FOR FREEING LATER!
void populate_renderer_data(renderer_data *rd, GLint num_vcs, GLint num_ids, vertex_t *vcs, GLuint *ids) {
	rd->num_vertices = num_vcs;
	rd->num_indices = num_ids;
	rd->vertices = vcs;
	rd->indices = ids;
}

// Assuming r->data filled. Only call once per renderer_t.
int renderer_init(renderer_t *r) {
	glGenVertexArrays(1, &r->VAO);
	glGenBuffers(1, &r->VBO);
	glGenBuffers(1, &r->EBO);

	glBindVertexArray(r->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * r->data.num_vertices, r->data.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * r->data.num_indices, r->data.indices, GL_STATIC_DRAW);

	r->vert.shader_type = GL_VERTEX_SHADER;
	r->frag.shader_type = GL_FRAGMENT_SHADER;
	if (shader_init(&r->vert) == EXIT_FAILURE) return EXIT_FAILURE;
	if (shader_init(&r->frag) == EXIT_FAILURE) return EXIT_FAILURE;
	r->shader_program = glCreateProgram();
	glAttachShader(r->shader_program, r->vert.shader);
	glAttachShader(r->shader_program, r->frag.shader);
	glLinkProgram(r->shader_program);

	int program_status;
	char program_log[512];
	glGetProgramiv(r->shader_program, GL_LINK_STATUS, &program_status);
	if (!program_status) {
		glGetProgramInfoLog(r->shader_program, 512, NULL, program_log);
		program_log_error(program_log);
		return EXIT_FAILURE;
	}

	glDeleteShader(r->vert.shader);
	glDeleteShader(r->frag.shader);

#if PROGRAM_OPENGL_INFO
	program_log_info("Shaders compiled. Program linked successfully.");
#endif

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, uv));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//use_renderer(NULL);
	return EXIT_SUCCESS;
}

int shader_init(shader_t *s) {
	s->shader = glCreateShader(s->shader_type);
	glShaderSource(s->shader, 1, &s->shader_source, NULL);
	glCompileShader(s->shader);

	// Check.
	int shader_status;
	char shader_log[512];
	glGetShaderiv(s->shader, GL_COMPILE_STATUS, &shader_status);
	if (!shader_status) {
		glGetShaderInfoLog(s->shader, 512, NULL, shader_log);
		program_log_error(shader_log);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void use_renderer(renderer_t *r) {
	if (!r) {
		glBindVertexArray(0);
		return;
	}
	glUseProgram(r->shader_program);
	glBindVertexArray(r->VAO);
}
