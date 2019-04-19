#pragma once

#include "renderer/tasks/task.h"
#include "scene/scene.h"
#include "lparse.h"

#include <memory>

namespace LRender {
	class Renderer::Task::Exposure final : public Task {
	public:
		Exposure(
			std::shared_ptr<LRender::Scene> scene,
			LParse::Randomizer randomizer,
			size_t threads);
		void perform(Renderer &renderer) override final;

	private:
		std::shared_ptr<LRender::Scene> scene;
		LParse::Randomizer randomizer;
		const size_t threads;
	};
}