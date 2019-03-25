#pragma once

#include "renderer/tasks/task.h"
#include "scene/scene.h"
#include "lparse.h"

#include <memory>

namespace LRender {
	class Renderer::Task::Exposure final : public Task {
	public:
		Exposure(std::shared_ptr<Scene> scene, LParse::Randomizer randomizer);
		void perform(Renderer &renderer) override final;

	private:
		std::shared_ptr<Scene> scene;
		LParse::Randomizer randomizer;
	};
}