layout(location = 0) in vec2 position;

out vec2 uv;

void main() {
	uv = position;

	gl_Position = vec4(vec2(-1) + position * 2, 0, 1);
}