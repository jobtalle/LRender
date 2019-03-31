#include "taskScene.h"

using namespace LRender;

Renderer::Task::Scene::Scene(std::shared_ptr<LRender::Scene> scene, LParse::Randomizer randomizer) :
	scene(std::move(scene)),
	randomizer(randomizer) {
	
}

void Renderer::Task::Scene::perform(Renderer& renderer) {
	renderer.loadScene(scene.get(), randomizer);
}
