#include "renderer.h"
#include "modeller/modeller.h"
#include "glad/glad.h"

using namespace LRender;

const std::string Renderer::FILE_SHADER_VERTEX_GEOMETRY = "glsl/vertexGeometry.glsl";
const std::string Renderer::FILE_SHADER_FRAGMENT_GEOMETRY = "glsl/fragmentGeometry.glsl";

bool Renderer::initialized = false;

Renderer::Renderer() {
	if(!initialized)
		initializeGL();

	shaderGeometry.reset(new Shader(FILE_SHADER_VERTEX_GEOMETRY, FILE_SHADER_FRAGMENT_GEOMETRY));
	shader = shaderGeometry.get();
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
	shader->use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto model : models)
		model->draw();
}

void Renderer::setSize(const size_t width, const size_t height) {
	glViewport(0, 0, width, height);
}

void Renderer::initializeGL() {
	gladLoadGL();

	initialized = true;
}

void Renderer::loadScene(const Scene *scene) {
	models.clear();

	for(auto agent : scene->getAgents()) {
		Modeller modeller(agent);

		models.push_back(modeller.getBranches());

		/*
		models.push_back(std::shared_ptr<Model>(new Model(
			{
				Vertex(Vector(-1, -1, 0), Vector(1, 0, 0)),
				Vertex(Vector(1, -1, 0), Vector(0, 1, 0)),
				Vertex(Vector(0, 1, 0), Vector(0, 0, 1))
			},
			{ 0, 1, 2 })));
			*/
	}
}