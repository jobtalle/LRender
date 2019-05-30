#include "taskSceneReport.h"
#include "renderer/target/renderTargetUint.h"
#include "renderer/passes/renderPassArea.h"
#include "renderer/passes/renderPassImage.h"
#include "math/constants.h"

#include <memory>
#include <utility>

using namespace LRender;

const size_t Renderer::Task::SceneReport::PROJECTION_SCALE = 64;
const size_t Renderer::Task::SceneReport::PROJECTION_COUNT = 2;

Renderer::Task::SceneReport::SceneReport(
	std::shared_ptr<LRender::Scene> scene,
	const LParse::Randomizer randomizer,
	const size_t threads,
	const bool highQuality) :
	scene(std::move(scene)),
	reportValue(report.get_future()),
	randomizer(randomizer),
	threads(threads),
	highQuality(highQuality) {

}

void Renderer::Task::SceneReport::perform(Renderer &renderer) {
	auto report = std::make_shared<Report>();

	renderer.loadScene(scene.get(), threads, highQuality, randomizer, report.get());

	if(!report->getAgents().empty()) {
		const auto scaleFactor = 2.0f / (PROJECTION_SCALE * PROJECTION_SCALE * PROJECTION_COUNT);
		std::vector<std::unique_ptr<RenderTargetUint>> targets;
		auto areaPass = RenderPassArea(report->getLimits());

		for(size_t projection = 0; projection < PROJECTION_COUNT; ++projection) {
			areaPass.setAngle(Constants::PI * (float(1 + projection) / (PROJECTION_COUNT + 1)));
			targets.push_back(std::make_unique<RenderTargetUint>(
				static_cast<size_t>(std::ceil(areaPass.getViewportWidth())) * PROJECTION_SCALE,
				static_cast<size_t>(std::ceil(areaPass.getViewportHeight())) * PROJECTION_SCALE));

			const auto &target = targets[targets.size() - 1];

			target->bind();
			target->clear();

			renderer.render(areaPass);

			target->download();
		}

		std::vector<unsigned int> histogram(scene->getAgents().size());
		std::fill(histogram.begin(), histogram.end(), 0);

		for(auto &target : targets)
			target->makeHistogram(histogram);

		for(size_t i = 0; i < scene->getAgents().size(); ++i) {
			auto exposure = ReportExposure(scaleFactor * histogram[i]);

			report->getAgents()[i].setExposure(exposure);
		}

		renderer.setMode(Renderer::Mode::DEFAULT);
	}

	renderer.setLastReport(report);
	this->report.set_value(report);
}

std::shared_ptr<Report> Renderer::Task::SceneReport::getReport() {
	return reportValue.get();
}