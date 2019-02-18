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

void Renderer::update() {
	std::lock_guard<std::mutex> lock(access);

	if(nextScene) {
		loadScene(nextScene.get());

		nextScene.reset();
	}
}

void Renderer::render() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::initializeGL() {
	gladLoadGL();

	initialized = true;
}

void Renderer::loadScene(const Scene *scene) {
	models.clear();

	for(auto agent : scene->getAgents())
		models.push_back(Model(
			{
				Vertex(Vector(-1, -1, 0), Vector(1, 0, 0)),
				Vertex(Vector(1, -1, 0), Vector(0, 1, 0)),
				Vertex(Vector(0, 1, 0), Vector(0, 0, 1))
			},
			{ 0, 1, 2 } ));
}