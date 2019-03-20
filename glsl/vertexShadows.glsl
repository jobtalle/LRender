layout(location = 0) in vec3 position;

void main() {
	gl_Position = depthProjection * vec4(position, 1);
}