#pragma once

#include "renderer/tasks/task.h"
#include "scene/scene.h"
#include "report/report.h"
#include "lparse.h"

#include <future>
#include <memory>

namespace LRender {
	class Renderer::Task::SceneReport final : public Task {
	public:
		SceneReport(std::shared_ptr<Scene> scene, LParse::Randomizer randomizer);
		void perform(Renderer &renderer) override final;
		const std::shared_ptr<Report> getReport();

	private:
		static const size_t PROJECTION_SCALE;
		static const size_t PROJECTION_COUNT;

		std::shared_ptr<Scene> scene;
		std::promise<std::shared_ptr<Report>> report;
		std::future<std::shared_ptr<Report>> reportValue;
		LParse::Randomizer randomizer;
	};
}