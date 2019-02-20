in vec3 interpolatedNormal;
in vec3 interpolatedColor;
out vec4 color;

void main()
{
	float l = max(0, dot(normalize(interpolatedNormal), normalize(vec3(1, 1, 1)))) * 0.8 + 0.2;
	color = vec4(interpolatedColor * l, 1);
}