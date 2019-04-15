#include "renderTargetUint.h"

#include <cmath>

using namespace LRender;

const unsigned int RenderTargetUint::VALUE_DEFAULT = 0xFFFF;

RenderTargetUint::RenderTargetUint(const size_t width, const size_t height) :
	RenderTarget(width, height, { makeTexture(width, height) }, true) {
	glGenBuffers(1, &pbo);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
	glBufferData(GL_PIXEL_PACK_BUFFER, (getWidth() * getHeight()) << 2, nullptr, GL_STREAM_READ);
}

RenderTargetUint::~RenderTargetUint() {
	glDeleteBuffers(1, &pbo);
	glDeleteTextures(1, &texture);
}

GLuint RenderTargetUint::getTexture() const {
	return texture;
}

void RenderTargetUint::download() const {
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
	glReadPixels(0, 0, getWidth(), getHeight(), GL_RED_INTEGER, GL_UNSIGNED_SHORT, nullptr);
}

void RenderTargetUint::makeHistogram(std::vector<unsigned>& histogram) const {
	bind();

	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);

	const auto pixels = static_cast<GLushort*>(glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY));
	const auto pixelCount = getWidth() * getHeight();

	for(size_t pixel = 0; pixel < pixelCount; ++pixel) if(pixels[pixel] != VALUE_DEFAULT)
		++*(histogram.begin() + pixels[pixel]);

	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
}

short RenderTargetUint::sample(const float x, const float y) const {
	bind();

	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);

	const auto pixels = static_cast<GLushort*>(glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY));
	const short value = pixels[
		static_cast<size_t>(std::round(x * getWidth())) +
		static_cast<size_t>(std::round((1 - y) * getHeight()) * getWidth())];

	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);

	return value;
}

void RenderTargetUint::clear() const {
	bind();

	const GLfloat depth = 1;

	glClearBufferuiv(GL_COLOR, 0, &VALUE_DEFAULT);
	glClearBufferfv(GL_DEPTH, 0, &depth);
}

GLuint RenderTargetUint::makeTexture(const size_t width, const size_t height) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, nullptr);

	return texture;
}
