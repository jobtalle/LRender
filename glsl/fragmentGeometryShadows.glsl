in vec3 interpolatedNormal;
in vec3 interpolatedColor;
in vec3 vertexPosition;

out vec4 color;

uniform sampler2D shadowMap;

void main()
{
	vec3 normal = normalize(interpolatedNormal);
	vec4 shadowCoord = depthProjection * vec4(vertexPosition, 1) * 0.5 + 0.5;

	if(texture(shadowMap, shadowCoord.xy).r + 0.005 < shadowCoord.z)
		color = vec4(0.5 * lightColor * interpolatedColor * (max(0, dot(normal, lightDirection)) * lightDiffuse + lightAmbient), 1);
	else
		color = vec4(lightColor * interpolatedColor * (max(0, dot(normal, lightDirection)) * lightDiffuse + lightAmbient), 1);

}