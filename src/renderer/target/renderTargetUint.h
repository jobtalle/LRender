#pragma once

#include "renderer/target/renderTarget.h"

#include <vector>

namespace LRender {
	class RenderTargetUint final : public RenderTarget {
	public:
		RenderTargetUint(size_t width, size_t height);
		~RenderTargetUint();
		GLuint getTexture() const;
		void download() const;
		void makeHistogram(std::vector<unsigned int> &histogram) const;
		short sample(float x, float y) const;
		void clear() const;

	private:
		static const unsigned int VALUE_DEFAULT;

		GLuint texture;
		GLuint pbo;

		GLuint makeTexture(size_t width, size_t height);
	};
}
