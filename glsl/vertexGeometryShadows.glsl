layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec3 interpolatedPosition;
out vec3 interpolatedNormal;
out vec2 interpolatedUV;

void main() {
	interpolatedPosition = position;
	interpolatedNormal = normal;
	interpolatedUV = uv;

	gl_Position = projection * vec4(position, 1);
}