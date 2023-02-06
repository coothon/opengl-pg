#include "include/window.h"

int clean_exit(program_t *p, int code) {
	if (p) {
		if (p->is_glfw) {
			if (p->window) glfwDestroyWindow(p->window);
			glfwTerminate();
		}
		
		// Free shader sources; maybe this should be done once they are compiled, but ehhhh
		if (p->render.triangle_r.vert.shader_source) free((void *)p->render.triangle_r.vert.shader_source);
		if (p->render.triangle_r.frag.shader_source) free((void *)p->render.triangle_r.frag.shader_source);
		if (p->render.background_r.vert.shader_source) free((void *)p->render.background_r.vert.shader_source);
		if (p->render.background_r.frag.shader_source) free((void *)p->render.background_r.frag.shader_source);
		//if (p->render.triangle_r.data.vertices) free(p->render.triangle_r.data.vertices);
		//if (p->render.triangle_r.data.indices) free(p->render.triangle_r.data.indices);
		free(p);
	}
	return code;
}
