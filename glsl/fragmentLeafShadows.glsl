in vec3 interpolatedNormal;
in vec3 interpolatedColor;
in vec3 interpolatedPosition;

out vec4 color;

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
		shadow += 0.5 * texture(shadowMap, vec3(at + samples[i], z), bias);

	return shadow / 9.0;
}

void main() {
	vec3 normal = normalize(interpolatedNormal);
	const vec3 shadowCoords = (shadowsProjectionUV * vec4(interpolatedPosition, 1)).xyz;

	const float bias = max(0.05 * (1.0 - dot(normal, lightDirection)), 0.005);  
	const float light = sampleShadow(shadowCoords.xy, shadowCoords.z, bias);

	if(gl_FrontFacing) {
		float l = max(0, -dot(normal, lightDirection)) * lightDiffuse + lightAmbient;
		color = vec4(light * lightColor * interpolatedColor * l, 1);
	}
	else {
		float l = max(0, dot(normal, lightDirection)) * lightDiffuse + lightAmbient;
		color = vec4(light * lightColor * interpolatedColor * l, 1);
	}
}