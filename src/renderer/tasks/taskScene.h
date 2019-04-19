#pragma once

#include "renderer/tasks/task.h"

namespace LRender {
	class Renderer::Task::Scene final : public Task {
	public:
		Scene(
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