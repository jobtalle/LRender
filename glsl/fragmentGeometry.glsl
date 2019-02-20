in vec3 interpolatedNormal;
in vec3 interpolatedColor;
out vec4 color;

void main()
{
	float l = dot(interpolatedNormal, normalize(vec3(1, 1, 1)));
	color = vec4(interpolatedColor * l, 1);
}