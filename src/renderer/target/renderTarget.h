#pragma once

#include "glad/glad.h"

#include <vector>
#include <cstddef>
#include "math/vector.h"

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
		static const float BORDER_COLOR[4];

		const size_t width;
		const size_t height;
		const bool depth;
		GLuint depthTexture;
		GLuint framebuffer;

		void createDepth(const bool border);
		void freeDepth();
	};
}
