#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

uniform float uptime;
uniform vec2 resolution;
uniform vec2 mouse_pos;

out vec3 color;
out vec2 uv;

vec2 screen_project(vec2 pos) {
	return (pos / resolution) * 2.0 - 1.0;
}

void main(void) {
	float scale = 300.0f;
	color = aCol;
	uv = aTex;
	gl_Position = vec4(screen_project((aPos * scale) + (resolution * 0.5) + vec2(mouse_pos.x, -mouse_pos.y)), 0.0f, 1.0f);
}