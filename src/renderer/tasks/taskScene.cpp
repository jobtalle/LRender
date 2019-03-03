#include "taskScene.h"

using namespace LRender;

Renderer::Task::Scene::Scene(
	const std::shared_ptr<LRender::Scene> scene,
	const std::function<void(Report&)> callback) :
	scene(scene),
	callback(callback) {

}

void Renderer::Task::Scene::perform(Renderer &renderer) const {
	Report report;

	renderer.loadScene(scene.get(), report);

	callback(report);
}