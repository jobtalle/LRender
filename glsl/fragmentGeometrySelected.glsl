in vec3 interpolatedNormal;
in vec3 interpolatedColor;
in vec3 interpolatedPosition;

out vec4 color;

void main() {
	const vec3 normal = normalize(interpolatedNormal);

	color = vec4(1.5 * lightColor * interpolatedColor * max(0.5, -dot(normal, lightDirection) * lightDiffuse + lightAmbient), 1);
}