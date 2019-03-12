#include "taskSceneReport.h"
#include "renderer/target/renderTargetColor.h"
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

void Renderer::Task::SceneReport::perform(Renderer &renderer) {
	auto report = std::make_shared<Report>();

	renderer.loadScene(scene.get(), report.get());

	if(!report->getAgents().empty()) {
		auto areaPass = RenderPassArea(report->getLimits());
		areaPass.setAngle(Constants::PI * 0.5f);

		// TODO: For each angle, create a texture and perform a render pass. Execute a read command to a PBO.

		const size_t scale = 32;
		const auto target = std::make_shared<RenderTargetColor>(
			static_cast<size_t>(std::ceil(areaPass.getViewportWidth())) * scale,
			static_cast<size_t>(std::ceil(areaPass.getViewportHeight())) * scale);

		target->bind();
		renderer.render(areaPass);
		renderer.bindDefault();

		renderer.setPass(std::make_shared<RenderPassImage>(target));

		// TODO: Read all blitted pixels from the PBO's and calculate exposure.
	}

	this->report.set_value(report);
}

const std::shared_ptr<Report> Renderer::Task::SceneReport::getReport() {
	reportValue.wait();

	return reportValue.get();
}