layout(std140, binding = 2) uniform uniformsLight {
	vec3 lightDirection;
	float lightDiffuse;
	vec3 lightColor;
	float lightAmbient;
};