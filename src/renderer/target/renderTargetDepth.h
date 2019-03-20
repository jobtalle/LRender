#pragma once

#include "renderer/target/renderTarget.h"

namespace LRender {
	class RenderTargetDepth final : public RenderTarget {
	public:
		RenderTargetDepth(const size_t width, const size_t height);
	};
}