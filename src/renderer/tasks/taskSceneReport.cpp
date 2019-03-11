#include "taskSceneReport.h"
#include "renderer/target/renderTargetColor.h"
#include "renderer/passes/renderPassArea.h"

using namespace LRender;

Renderer::Task::SceneReport::SceneReport(const std::shared_ptr<LRender::Scene> scene) :
	scene(scene),
	reportValue(report.get_future()) {

}

void Renderer::Task::SceneReport::perform(Renderer &renderer) {
	auto report = std::make_shared<Report>();

	renderer.loadScene(scene.get(), report.get());

	auto target = RenderTargetColor(800, 600);
	auto areaPass = RenderPassArea();
	target.bind();
	renderer.render(areaPass);
	renderer.bindDefault();

	this->report.set_value(report);
}

const std::shared_ptr<Report> Renderer::Task::SceneReport::getReport() {
	reportValue.wait();

	return reportValue.get();
}