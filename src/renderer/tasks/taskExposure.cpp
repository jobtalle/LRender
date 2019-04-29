#include "taskExposure.h"
#include "renderer/passes/renderPassArea.h"
#include "math/constants.h"
#include "renderer/target/renderTargetUint.h"
#include "renderer/passes/renderPassInteger.h"

using namespace LRender;

Renderer::Task::Exposure::Exposure(
	std::shared_ptr<LRender::Scene> scene,
	const LParse::Randomizer randomizer,
	const size_t threads) :
	scene(std::move(scene)),
	randomizer(randomizer),
	threads(threads) {
	
}

void Renderer::Task::Exposure::perform(Renderer& renderer) {
	auto report = std::make_shared<Report>();

	renderer.loadScene(
		scene.get(),
		threads,
		false,
		randomizer,
		report.get());

	if(!report->getAgents().empty()) {
		auto areaPass = RenderPassArea(report->getLimits());
		areaPass.setAngle(Constants::PI * 0.5f);

		const auto targetUint = std::make_shared<RenderTargetUint>(renderer.getWidth(), renderer.getHeight());

		targetUint->bind();
		targetUint->clear();

		renderer.render(areaPass);
		renderer.setPass(std::make_shared<RenderPassInteger>(targetUint));
	}
}
