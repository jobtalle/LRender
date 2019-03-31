#pragma once

#include "renderer/tasks/task.h"

namespace LRender {
	class Renderer::Task::Scene final : public Task {
	public:
		Scene(std::shared_ptr<LRender::Scene> scene, LParse::Randomizer randomizer);
		void perform(Renderer &renderer) override final;

	private:
		std::shared_ptr<LRender::Scene> scene;
		LParse::Randomizer randomizer;
	};
}