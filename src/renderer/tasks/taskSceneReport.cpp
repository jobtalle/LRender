#include "taskSceneReport.h"
#include "renderer/target/renderTargetColor.h"
#include "renderer/passes/renderPassArea.h"
#include "renderer/passes/renderPassImage.h"

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

	const auto target = std::make_shared<RenderTargetColor>(800, 600);
	auto areaPass = RenderPassArea();
	target->bind();
	renderer.render();
	renderer.bindDefault();

	renderer.setPass(std::make_shared<RenderPassImage>(target));

	this->report.set_value(report);
}

const std::shared_ptr<Report> Renderer::Task::SceneReport::getReport() {
	reportValue.wait();

	return reportValue.get();
}