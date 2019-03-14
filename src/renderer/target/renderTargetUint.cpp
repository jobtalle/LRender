#include "renderTargetUint.h"

using namespace LRender;

RenderTargetUint::RenderTargetUint(const size_t width, const size_t height) :
	RenderTarget(width, height, { makeTexture(width, height) }) {
	
}

RenderTargetUint::~RenderTargetUint() {
	glDeleteTextures(1, &texture);
}

GLuint RenderTargetUint::makeTexture(const size_t width, const size_t height) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);

	return texture;
}
