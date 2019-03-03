#pragma once

#include "renderer/tasks/task.h"
#include "scene/scene.h"
#include "report/report.h"

namespace LRender {
	class Renderer::Task::Scene final : public Renderer::Task {
	public:
		Scene(
			std::shared_ptr<LRender::Scene> scene,
			const std::function<void(Report&)> callback);
		void perform(Renderer &renderer) const override final;

	private:
		std::shared_ptr<LRender::Scene> scene;
		const std::function<void(Report&)> callback;
	};
};