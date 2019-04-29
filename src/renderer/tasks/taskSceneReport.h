#pragma once

#include "renderer/tasks/task.h"
#include "report/report.h"
#include "lparse.h"

#include <future>
#include <memory>

namespace LRender {
	class Renderer::Task::SceneReport final : public Task {
	public:
		SceneReport(
			std::shared_ptr<LRender::Scene> scene,
			LParse::Randomizer randomizer,
			size_t threads,
			bool highQuality);
		void perform(Renderer &renderer) override final;
		std::shared_ptr<Report> getReport();

	private:
		static const size_t PROJECTION_SCALE;
		static const size_t PROJECTION_COUNT;

		std::shared_ptr<LRender::Scene> scene;
		std::promise<std::shared_ptr<Report>> report;
		std::future<std::shared_ptr<Report>> reportValue;
		LParse::Randomizer randomizer;
		const size_t threads;
		const bool highQuality;
	};
}