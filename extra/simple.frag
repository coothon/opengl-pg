#version 460 core
out vec4 FragColor;

in vec3 color;
in vec2 uv;

void main(void) {
	FragColor = vec4(color, 1.0f);
}