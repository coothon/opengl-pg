#include "window.h"

int clean_exit(program_t *p, int code) {
	if (p) {
		if (p->is_glfw) {
			if (p->window) glfwDestroyWindow(p->window);
			glfwTerminate();
		}
		if (p->timing) free(p->timing);
		if (p->render) {
			if (p->render->RENDERER1) free(p->render->RENDERER1);
			if (p->render->simple_vert) {
				if (p->render->simple_vert->shader_source) free(p->render->simple_vert->shader_source);
				free(p->render->simple_vert);
			}
			if (p->render->simple_frag) {
				if (p->render->simple_frag->shader_source) free(p->render->simple_frag->shader_source);
				free(p->render->simple_frag);
			}
			free(p->render);
		}
		free(p);
	}
	return code;
}
