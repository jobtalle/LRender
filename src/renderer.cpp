#include "renderer.h"
#include "glad/glad.h"

using namespace LRender;

bool Renderer::initialized = false;

Renderer::Renderer() {
	if(!initialized)
		initializeGL();

	glClearColor(1, 0, 0, 1);
}

void Renderer::setScene(std::shared_ptr<Scene> scene) {
	std::lock_guard<std::mutex> lock(access);

	nextScene = scene;
}

void Renderer::render() {
	std::lock_guard<std::mutex> lock(access);

	if(nextScene) {
		loadScene(nextScene.get());

		nextScene.reset();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::initializeGL() {
	gladLoadGL();

	initialized = true;
}

void Renderer::loadScene(const Scene *scene) {

}