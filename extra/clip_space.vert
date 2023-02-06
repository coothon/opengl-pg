#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

uniform vec2 scale;

out vec3 color;
out vec2 uv;

void main(void) {
	color = aCol;
	uv = aUV;
	gl_Position = vec4(aPos * scale, 0.0f, 1.0f);
}