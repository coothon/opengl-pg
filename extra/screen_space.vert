// This is for renderers that need to be drawn in screen space.
// Use clip_space.vert if you want your vertices drawn as is, in clip space.
#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

uniform vec2 resolution;
uniform vec2 mouse_pos;
uniform vec2 offset_pos;
uniform vec2 scale;

out vec3 color;
out vec2 uv;

vec2 screen_project(vec2 pos) {
	return (pos / resolution) * 2.0 - 1.0;
}

void main(void) {
	color = aCol;
	uv = aUV;
	vec2 scaled = aPos * scale;
	gl_Position = vec4(screen_project((scaled) + (resolution * 0.5f) + offset_pos), 0.0f, 1.0f);
}