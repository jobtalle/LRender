#pragma once

#include "renderer/target/renderTarget.h"

#include <vector>

namespace LRender {
	class RenderTargetUint final : public RenderTarget {
	public:
		RenderTargetUint(const size_t width, const size_t height);
		~RenderTargetUint();
		void makeHistogram(std::vector<unsigned int> &histogram) const;
		void clear() const;

	private:
		static const unsigned int VALUE_DEFAULT = 0xFFFFFFFF;

		GLuint texture;

		GLuint makeTexture(const size_t width, const size_t height);
	};
}