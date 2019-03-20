#pragma once

#include "glad/glad.h"

#include <vector>
#include <cstddef>

namespace LRender {
	class RenderTarget {
	public:
		RenderTarget(
			const size_t width,
			const size_t height,
			const std::vector<GLuint> &textures,
			const bool depth = false);
		~RenderTarget();
		void bind() const;
		size_t getWidth() const;
		size_t getHeight() const;
		GLuint getDepth() const;

	private:
		const size_t width;
		const size_t height;
		const bool depth;
		GLuint depthTexture;
		GLuint framebuffer;

		void createDepth();
		void freeDepth();
	};
}
