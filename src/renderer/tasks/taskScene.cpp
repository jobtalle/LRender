#include "taskScene.h"

using namespace LRender;

Renderer::Task::Scene::Scene(const std::shared_ptr<LRender::Scene> scene) :
	scene(scene),
	reportValue(report.get_future()) {

}

void Renderer::Task::Scene::perform(Renderer &renderer) {
	auto report = std::make_shared<Report>();

	renderer.loadScene(scene.get(), report.get());

	this->report.set_value(report);
}

const std::shared_ptr<Report> Renderer::Task::Scene::getReport() {
	reportValue.wait();

	return reportValue.get();
}