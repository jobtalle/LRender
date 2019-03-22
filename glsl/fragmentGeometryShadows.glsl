in vec3 interpolatedNormal;
in vec3 interpolatedColor;
in vec3 interpolatedPosition;

out vec4 color;

void main() {
	const vec3 normal = normalize(interpolatedNormal);
	const vec3 shadowCoords = (shadowsProjectionUV * vec4(interpolatedPosition, 1)).xyz;

	const float bias = max(0.005 * (1.0 + dot(normal, lightDirection)), 0.001);  
	const float light = sampleShadow(shadowCoords.xy, shadowCoords.z, bias);

	color = vec4(light * lightColor * interpolatedColor * max(0, -dot(normal, lightDirection) * lightDiffuse + lightAmbient), 1);
}