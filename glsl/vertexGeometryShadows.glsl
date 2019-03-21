layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

out vec3 interpolatedNormal;
out vec3 interpolatedColor;
out vec3 interpolatedPosition;

void main() {
	interpolatedNormal = normal;
	interpolatedColor = color;
	interpolatedPosition = position;

	gl_Position = projection * vec4(position, 1);
}