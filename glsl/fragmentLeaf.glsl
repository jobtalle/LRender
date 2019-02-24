in vec3 interpolatedNormal;
in vec3 interpolatedColor;
out vec4 color;

void main()
{
	vec3 light = normalize(vec3(1, 1, 1));
	vec3 normal = normalize(interpolatedNormal);

	if(gl_FrontFacing) {
		float l = max(0, dot(normal, light)) * 0.8 + 0.2;
		color = vec4(interpolatedColor * l, 1);
	}
	else {
		float l = max(0, dot(-normal, light)) * 0.8 + 0.2;
		color = vec4(interpolatedColor * l, 1);
	}
}