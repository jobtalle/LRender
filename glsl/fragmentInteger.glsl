uniform usampler2D image;

in vec2 uv;

out vec4 color;

const vec3 colors[4] = vec3[4](
	vec3(1, 0, 0),
	vec3(0, 1, 0),
	vec3(0, 0, 1),
	vec3(1, 1, 1)
);

void main()
{
	uint i = texture(image, uv).r;

	if(i == 0xFFFF)
		color = vec4(0, 0, 0, 1);
	else
		color = vec4(colors[i % 4], 1);
}