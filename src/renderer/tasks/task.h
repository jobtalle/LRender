#pragma once

#include "renderer/renderer.h"

namespace LRender {
	class Renderer::Task {
	public:
		class Mode;
		class SceneReport;
		class Exposure;

		virtual ~Task() = default;
		virtual void perform(Renderer &renderer) = 0;
	};
}