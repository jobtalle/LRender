#include "shaderImage.h"

using namespace LRender;

const std::string ShaderImage::SHADER_VERTEX = "LRender/glsl/vertexImage.glsl";
const std::string ShaderImage::SHADER_FRAGMENT = "LRender/glsl/fragmentImage.glsl";
const char *ShaderImage::IMAGE_NAME = "image";
const GLuint ShaderImage::CHANNEL = 0;

ShaderImage::ShaderImage() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT) {
	imageLocation = glGetUniformLocation(program, IMAGE_NAME);
}

void ShaderImage::setImage(const GLuint texture) const {
	glActiveTexture(GL_TEXTURE0 + CHANNEL);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(imageLocation, CHANNEL);
}