in vec3 interpolatedNormal;
in vec3 interpolatedColor;
in vec3 interpolatedPosition;

out vec4 color;

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