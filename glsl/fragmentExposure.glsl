uniform uint agent;

in vec2 rnd;

out uvec4 color;

void main()
{
	if (random(rnd) > 0.2)
		discard;

	color = uvec4(agent);
}