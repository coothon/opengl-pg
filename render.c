#include "include/render.h"

int render_init(render_t *r, renderer *R, shader_t *v, shader_t *f) {
	glGenVertexArrays(1, &R->VAO);
	glBindVertexArray(R->VAO);
	glGenBuffers(1, &R->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, R->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tt_vertices), tt_vertices, GL_STATIC_DRAW);

	if (shader_init(v) == EXIT_FAILURE) return EXIT_FAILURE;
	if (shader_init(f) == EXIT_FAILURE) return EXIT_FAILURE;

	R->shader_program = glCreateProgram();
	glAttachShader(R->shader_program, v->shader);
	glAttachShader(R->shader_program, f->shader);
	glLinkProgram(R->shader_program);
	
	// Check.
	int program_status;
	char program_log[512];
	glGetProgramiv(R->shader_program, GL_LINK_STATUS, &program_status);
	if (!program_status) {
		glGetProgramInfoLog(R->shader_program, 512, NULL, program_log);
		program_log_error(program_log);
		return EXIT_FAILURE;
	}

	glDeleteShader(v->shader);
	glDeleteShader(f->shader);

#ifdef PROGRAM_OPENGL_INFO
	program_log_info("Shaders compiled. Program linked successfully.");
#endif

	glVertexAttribPointer(0,
						  3,
						  GL_FLOAT,
						  GL_FALSE,
						  3 * sizeof(float),
						  (void*)0);
	glEnableVertexAttribArray(0);
	
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
