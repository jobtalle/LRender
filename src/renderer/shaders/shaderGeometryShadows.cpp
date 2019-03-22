#include "shaderGeometryShadows.h"

using namespace LRender;

const std::string ShaderGeometryShadows::SHADER_VERTEX = "LRender/glsl/vertexGeometryShadows.glsl";
const std::string ShaderGeometryShadows::SHADER_FRAGMENT = "LRender/glsl/fragmentGeometryShadows.glsl";
const std::string ShaderGeometryShadows::SHADER_SHADOWS = "LRender/glsl/shadows.glsl";
const char *ShaderGeometryShadows::SHADOW_MAP_NAME = "shadowMap";
const GLuint ShaderGeometryShadows::CHANNEL = 0;

ShaderGeometryShadows::ShaderGeometryShadows() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT, { SHADER_SHADOWS }) {
	shadowMapLocation = glGetUniformLocation(program, SHADOW_MAP_NAME);
}

void ShaderGeometryShadows::setShadowMap(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shadowMapLocation, CHANNEL);
}
