#pragma once

#include "renderer/target/renderTarget.h"

#include <vector>

namespace LRender {
	class RenderTargetUint final : public RenderTarget {
	public:
		RenderTargetUint(const size_t width, const size_t height);
		~RenderTargetUint();
		GLuint getTexture() const;
		void prepareHistogram() const;
		void makeHistogram(std::vector<unsigned int> &histogram) const;
		void clear() const;

	private:
		static const unsigned int VALUE_DEFAULT;

		GLuint texture;
		GLuint pbo;

		GLuint makeTexture(const size_t width, const size_t height);
	};
}
