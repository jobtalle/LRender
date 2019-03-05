#pragma once

#include "renderer/tasks/task.h"
#include "scene/scene.h"
#include "report/report.h"

#include <future>
#include <memory>

namespace LRender {
	class Renderer::Task::SceneReport final : public Renderer::Task {
	public:
		SceneReport(const std::shared_ptr<LRender::Scene> scene);
		void perform(Renderer &renderer) override final;
		const std::shared_ptr<Report> getReport();

	private:
		std::promise<std::shared_ptr<Report>> report;
		std::future<std::shared_ptr<Report>> reportValue;
		std::shared_ptr<LRender::Scene> scene;
	};
};