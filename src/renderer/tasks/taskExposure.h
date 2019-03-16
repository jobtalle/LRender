#pragma once

#include "renderer/tasks/task.h"
#include "scene/scene.h"

#include <memory>

namespace LRender {
	class Renderer::Task::Exposure final : public Task {
	public:
		Exposure(std::shared_ptr<Scene> scene);
		void perform(Renderer &renderer) override final;

	private:
		std::shared_ptr<Scene> scene;
	};
}