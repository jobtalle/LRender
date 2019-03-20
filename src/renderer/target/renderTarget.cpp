#include "renderTarget.h"

using namespace LRender;

RenderTarget::RenderTarget(
	const size_t width,
	const size_t height,
	const std::vector<GLuint> &textures,
	const bool depth) :
	width(width),
	height(height),
	depth(depth) {
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	if(textures.empty())
		glDrawBuffer(GL_NONE);
	else for(size_t i = 0; i < textures.size(); ++i)
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);

	if(depth)
		createDepth();
}

RenderTarget::~RenderTarget() {
	glDeleteFramebuffers(1, &framebuffer);

	if(depth)
		freeDepth();
}

void RenderTarget::bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);
}

size_t RenderTarget::getWidth() const {
	return width;
}

size_t RenderTarget::getHeight() const {
	return height;
}

GLuint RenderTarget::getDepth() const {
	return depthTexture;
}

void RenderTarget::createDepth() {
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_DEPTH_COMPONENT16,
		width,
		height,
		0,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void RenderTarget::freeDepth() {
	glDeleteTextures(1, &depthTexture);
}
