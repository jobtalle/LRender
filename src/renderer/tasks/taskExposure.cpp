#include "taskExposure.h"
#include "renderer/passes/renderPassArea.h"
#include "math/constants.h"
#include "renderer/target/renderTargetUint.h"
#include "renderer/passes/renderPassInteger.h"

using namespace LRender;

Renderer::Task::Exposure::Exposure(std::shared_ptr<Scene> scene) :
	scene(std::move(scene)) {
	
}

void Renderer::Task::Exposure::perform(Renderer& renderer) {
	auto report = std::make_shared<Report>();

	renderer.loadScene(scene.get(), report.get());

	if(!report->getAgents().empty()) {
		auto areaPass = RenderPassArea(report->getLimits());
		areaPass.setAngle(Constants::PI * 0.5f);

		const size_t scale = 32;
		const auto targetUint = std::make_shared<RenderTargetUint>(
			static_cast<size_t>(std::ceil(areaPass.getViewportWidth())) * scale,
			static_cast<size_t>(std::ceil(areaPass.getViewportHeight())) * scale);

		targetUint->bind();
		targetUint->clear();

		renderer.render(areaPass);
		renderer.setPass(std::make_shared<RenderPassInteger>(targetUint));
	}
}
