#include "shaderGeometryShadows.h"

using namespace LRender;

const std::string ShaderGeometryShadows::SHADER_VERTEX = "LRender/glsl/vertexGeometryShadows.glsl";
const std::string ShaderGeometryShadows::SHADER_FRAGMENT = "LRender/glsl/fragmentGeometryShadows.glsl";
const std::string ShaderGeometryShadows::SHADER_SHADOWS = "LRender/glsl/shadows.glsl";
const char *ShaderGeometryShadows::SHADOW_MAP_NAME = "shadowMap";
const char *ShaderGeometryShadows::COLORS_NAME = "colors";
const GLuint ShaderGeometryShadows::CHANNEL_SHADOWS = 0;
const GLuint ShaderGeometryShadows::CHANNEL_COLORS = 1;

ShaderGeometryShadows::ShaderGeometryShadows() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT, { SHADER_SHADOWS }) {
	shadowMapLocation = glGetUniformLocation(program, SHADOW_MAP_NAME);
	colorsLocation = glGetUniformLocation(program, COLORS_NAME);
}

void ShaderGeometryShadows::setShadowMap(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL_SHADOWS);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shadowMapLocation, CHANNEL_SHADOWS);
}

void ShaderGeometryShadows::setColors(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL_COLORS);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(colorsLocation, CHANNEL_COLORS);
}
