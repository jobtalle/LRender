#include "shaderLeavesShadows.h"

using namespace LRender;

const std::string ShaderLeavesShadows::SHADER_VERTEX = "LRender/glsl/vertexGeometryShadows.glsl";
const std::string ShaderLeavesShadows::SHADER_FRAGMENT = "LRender/glsl/fragmentLeafShadows.glsl";
const char *ShaderLeavesShadows::SHADOW_MAP_NAME = "shadowMap";
const GLuint ShaderLeavesShadows::CHANNEL = 0;

ShaderLeavesShadows::ShaderLeavesShadows() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT) {
	shadowMapLocation = glGetUniformLocation(program, SHADOW_MAP_NAME);
}

void ShaderLeavesShadows::setShadowMap(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shadowMapLocation, CHANNEL);
}
