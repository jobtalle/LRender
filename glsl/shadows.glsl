uniform sampler2DShadow shadowMap;

const vec2 pixel = 1.0 / textureSize(shadowMap, 0);
const vec2 samples[9] = vec2[](
	-pixel,
	vec2(0, -pixel.y),
	vec2(pixel.x, -pixel.y),
	vec2(-pixel.x, 0),
	vec2(0, 0),
	vec2(pixel.x, 0),
	vec2(-pixel.x, pixel.y),
	vec2(0, pixel.y),
	pixel
);

float sampleShadow(vec2 at, float z, float bias) {
	float shadow = 4.5;

	for(int i = 0; i < 9; ++i)
		shadow += 0.5 * texture(shadowMap, vec3(at + samples[i], z - bias));

	return shadow / 9.0;
}
