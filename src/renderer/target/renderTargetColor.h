#pragma once

#include "renderer/target/renderTarget.h"

#include <stdlib.h>

namespace LRender {
	class RenderTargetColor final : public RenderTarget {
	public:
		RenderTargetColor(const size_t width, const size_t height);
		~RenderTargetColor();
		GLuint getTexture() const;

	private:
		GLuint texture;

		GLuint makeTexture(const size_t width, const size_t height);
	};
}
