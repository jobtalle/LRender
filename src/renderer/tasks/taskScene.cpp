#include "taskScene.h"

using namespace LRender;

Renderer::Task::Scene::Scene(
	std::shared_ptr<LRender::Scene> scene,
	const LParse::Randomizer randomizer,
	const size_t threads) :
	scene(std::move(scene)),
	randomizer(randomizer),
	threads(threads) {
	
}

void Renderer::Task::Scene::perform(Renderer& renderer) {
	renderer.loadScene(scene.get(), threads, randomizer);
}
