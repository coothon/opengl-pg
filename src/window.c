#include "include/window.h"

int clean_exit(program_t *p, int code) {
	if (p) {
		if (p->is_glfw) {
			if (p->window) glfwDestroyWindow(p->window);
			glfwTerminate();
		}
		if (p->render.RENDERER1.vert.shader_source) free(p->render.RENDERER1.vert.shader_source);
		if (p->render.RENDERER1.frag.shader_source) free(p->render.RENDERER1.frag.shader_source);
		//if (p->render.RENDERER1.data.vertices) free(p->render.RENDERER1.data.vertices);
		//if (p->render.RENDERER1.data.indices) free(p->render.RENDERER1.data.indices);
		free(p);
	}
	return code;
}
