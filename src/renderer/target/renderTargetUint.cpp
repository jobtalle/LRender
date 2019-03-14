#include "renderTargetUint.h"

using namespace LRender;

RenderTargetUint::RenderTargetUint(const size_t width, const size_t height) :
	RenderTarget(width, height, { makeTexture(width, height) }) {
	
}

RenderTargetUint::~RenderTargetUint() {
	glDeleteTextures(1, &texture);
}

void RenderTargetUint::makeHistogram(std::vector<unsigned>& histogram) const {
	bind();

	const size_t pixelCount = getWidth() * getHeight();
	GLuint pbo;

	glGenBuffers(1, &pbo);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
	glBufferData(GL_PIXEL_PACK_BUFFER, pixelCount << 2, nullptr, GL_STREAM_READ);
	glReadPixels(0, 0, getWidth(), getHeight(), GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);

	const auto pixels = static_cast<GLuint*>(glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY));

	for(size_t pixel = 0; pixel < pixelCount; ++pixel) if(pixels[pixel] != VALUE_DEFAULT)
		++*(histogram.begin() + pixels[pixel] + 1);

	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
}

void RenderTargetUint::clear() const {
	bind();

	glClearBufferuiv(GL_COLOR, 0, &VALUE_DEFAULT);
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
