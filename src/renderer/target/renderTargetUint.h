#pragma once

#include "renderer/target/renderTarget.h"

namespace LRender {
	class RenderTargetUint final : public RenderTarget {
	public:
		RenderTargetUint(const size_t width, const size_t height);
		~RenderTargetUint();

	private:
		GLuint texture;

		GLuint makeTexture(const size_t width, const size_t height);
	};
}