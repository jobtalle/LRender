#include "renderTargetColor.h"

using namespace LRender;

RenderTargetColor::RenderTargetColor(const size_t width, const size_t height) :
	RenderTarget(width, height, { makeTexture(width, height) }) {
	
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	return texture;
}