#version 460 core
out vec4 FragColor;

uniform float uptime_sin;

in vec3 color;
in vec2 uv;

void main(void) {
	FragColor = vec4(uv.y * (1.0f - uptime_sin), uv.x * uptime_sin, 1.0f * (uptime_sin), 1.0f);
}
