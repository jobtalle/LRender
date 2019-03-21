layout(location = 0) in vec3 position;

void main() {
	gl_Position = shadowsProjection * vec4(position, 1);
}