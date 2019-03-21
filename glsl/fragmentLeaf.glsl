in vec3 interpolatedNormal;
in vec3 interpolatedColor;
out vec4 color;

void main() {
	vec3 normal = normalize(interpolatedNormal);

	if(gl_FrontFacing) {
		float l = max(0, dot(normal, lightDirection)) * lightDiffuse + lightAmbient;
		color = vec4(lightColor * interpolatedColor * l, 1);
	}
	else {
		float l = max(0, dot(-normal, lightDirection)) * lightDiffuse + lightAmbient;
		color = vec4(lightColor * interpolatedColor * l, 1);
	}
}