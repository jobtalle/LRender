#include "shaderLeavesShadows.h"

using namespace LRender;

const std::string ShaderLeavesShadows::SHADER_VERTEX = "LRender/glsl/vertexGeometryShadows.glsl";
const std::string ShaderLeavesShadows::SHADER_FRAGMENT = "LRender/glsl/fragmentLeafShadows.glsl";
const std::string ShaderLeavesShadows::SHADER_SHADOWS = "LRender/glsl/shadows.glsl";
const char *ShaderLeavesShadows::SHADOW_MAP_NAME = "shadowMap";
const char *ShaderLeavesShadows::COLORS_NAME = "colors";
const GLuint ShaderLeavesShadows::CHANNEL_SHADOWS = 0;
const GLuint ShaderLeavesShadows::CHANNEL_COLORS = 1;

ShaderLeavesShadows::ShaderLeavesShadows() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT, { SHADER_SHADOWS }) {
	shadowMapLocation = glGetUniformLocation(program, SHADOW_MAP_NAME);
	colorsLocation = glGetUniformLocation(program, COLORS_NAME);
}

void ShaderLeavesShadows::setShadowMap(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL_SHADOWS);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shadowMapLocation, CHANNEL_SHADOWS);
}

void ShaderLeavesShadows::setColors(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL_COLORS);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(colorsLocation, CHANNEL_COLORS);
}
