in vec3 interpolatedNormal;
in vec3 interpolatedColor;
out vec4 color;

void main() {
	vec3 normal = normalize(interpolatedNormal);

	color = vec4(lightColor * interpolatedColor * (max(0, -dot(normal, lightDirection)) * lightDiffuse + lightAmbient), 1);
}