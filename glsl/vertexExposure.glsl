layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

out vec2 rnd;

void main() {
	gl_Position = projection * vec4(position, 1);
	rnd = position.xy;
}