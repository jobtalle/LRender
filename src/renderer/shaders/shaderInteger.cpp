#include "shaderInteger.h"

using namespace LRender;

const std::string ShaderInteger::SHADER_VERTEX = "LRender/glsl/vertexImage.glsl";
const std::string ShaderInteger::SHADER_FRAGMENT = "LRender/glsl/fragmentInteger.glsl";
const char *ShaderInteger::IMAGE_NAME = "image";
const GLuint ShaderInteger::CHANNEL = 0;

ShaderInteger::ShaderInteger() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT) {
	imageLocation = glGetUniformLocation(program, IMAGE_NAME);
}

void ShaderInteger::setImage(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(imageLocation, CHANNEL);
}