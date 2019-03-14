#include "taskSceneReport.h"
#include "renderer/target/renderTargetUint.h"
#include "renderer/passes/renderPassArea.h"
#include "renderer/passes/renderPassImage.h"
#include "math/constants.h"

#include <memory>
#include <utility>

using namespace LRender;

Renderer::Task::SceneReport::SceneReport(std::shared_ptr<LRender::Scene> scene) :
	scene(std::move(scene)),
	reportValue(report.get_future()) {

}
#include <iostream>
void Renderer::Task::SceneReport::perform(Renderer &renderer) {
	auto report = std::make_shared<Report>();

	renderer.loadScene(scene.get(), report.get());

	if(!report->getAgents().empty()) {
		auto areaPass = RenderPassArea(report->getLimits());
		areaPass.setAngle(Constants::PI * 0.5f);

		const size_t scale = 32;
		const auto target = std::make_shared<RenderTargetUint>(
			static_cast<size_t>(std::ceil(areaPass.getViewportWidth())) * scale,
			static_cast<size_t>(std::ceil(areaPass.getViewportHeight())) * scale);

		target->bind();
		target->clear();

		renderer.render(areaPass);
		renderer.setMode(Renderer::Mode::DEFAULT);

		// TODO: Read all blitted pixels from the PBO's and calculate exposure.

		std::vector<unsigned int> histogram(scene->getAgents().size());
		std::fill(histogram.begin(), histogram.end(), 0);

		target->makeHistogram(histogram);

		for(size_t i = 0; i < scene->getAgents().size(); ++i)
			std::cout << "Agent #" << i << " " << histogram[i] << std::endl;
	}

	this->report.set_value(report);
}

const std::shared_ptr<Report> Renderer::Task::SceneReport::getReport() {
	reportValue.wait();

	return reportValue.get();
}