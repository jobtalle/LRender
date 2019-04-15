in vec3 interpolatedNormal;
in vec3 interpolatedColor;
out vec4 color;

void main() {
	vec3 normal = normalize(interpolatedNormal);

	float l = abs(dot(normal, lightDirection)) * lightDiffuse + lightAmbient;
	color = vec4(lightColor * interpolatedColor * l, 1);
}