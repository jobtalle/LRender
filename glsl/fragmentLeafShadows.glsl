in vec3 interpolatedPosition;
in vec3 interpolatedNormal;
in vec2 interpolatedUV;

uniform sampler2D colors;

out vec4 color;

void main() {
	vec3 normal = normalize(interpolatedNormal);
	const vec3 shadowCoords = (shadowsProjectionUV * vec4(interpolatedPosition, 1)).xyz;

	const float bias = max(0.05 * (1.0 - dot(normal, lightDirection)), 0.005);  
	const float light = sampleShadow(shadowCoords.xy, shadowCoords.z, bias);
	float l = abs(dot(normal, lightDirection)) * lightDiffuse + lightAmbient;

	color = vec4(light * lightColor * texture(colors, interpolatedUV).rgb * l, 1);
}