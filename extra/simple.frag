#version 460 core
out vec4 FragColor;

uniform float uptime_sin;

in vec3 color;
in vec2 uv;

void main(void) {
	FragColor = vec4(color * uptime_sin, 1.0f);
}
