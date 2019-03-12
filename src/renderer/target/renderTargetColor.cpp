#include "renderTargetColor.h"

using namespace LRender;

RenderTargetColor::RenderTargetColor(const size_t width, const size_t height) :
	RenderTarget(width, height, { makeTexture(width, height) }, true) {
	
}

RenderTargetColor::~RenderTargetColor() {
	glDeleteTextures(1, &texture);
}

GLuint RenderTargetColor::getTexture() const {
	return texture;
}

GLuint RenderTargetColor::makeTexture(const size_t width, const size_t height) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	return texture;
}
