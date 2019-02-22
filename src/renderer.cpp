#include "renderer.h"
#include "modeller/radiusSampler.h"
#include "modeller/agentModel.h"
#include "glad/glad.h"

#include <math.h>

using namespace LRender;

const std::string Renderer::FILE_SHADER_VERTEX_GEOMETRY = "LRender/glsl/vertexGeometry.glsl";
const std::string Renderer::FILE_SHADER_FRAGMENT_GEOMETRY = "LRender/glsl/fragmentGeometry.glsl";
const float Renderer::PROJECTION_ANGLE = atan(1) * 1.5f;
const float Renderer::Z_NEAR = 0.05f;
const float Renderer::Z_FAR = 400;

Renderer::Renderer(const size_t width, const size_t height) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shaderGeometry.reset(new Shader(FILE_SHADER_VERTEX_GEOMETRY, FILE_SHADER_FRAGMENT_GEOMETRY));
	shader = shaderGeometry.get();

	setSize(width, height);
	updateProjection();
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

void Renderer::render() {
	updateUniforms();

	shader->use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto model : models)
		model->draw();
}

void Renderer::setSize(const size_t width, const size_t height) {
	glViewport(0, 0, width, height);

	aspect = float(width) / height;

	updateProjection();
}

void Renderer::mouseMove(const size_t x, const size_t y) {
	orbit.mouseMove(x, y);
}

void Renderer::mousePress(const MouseButton button) {
	switch(button) {
	case MOUSE_DRAG:
		orbit.mouseGrabDrag();

		break;
	case MOUSE_PAN:
		orbit.mouseGrabPan();
		
		break;
	}
}

void Renderer::mouseRelease(const MouseButton button) {
	switch(button) {
	case MOUSE_DRAG:
		orbit.mouseReleaseDrag();

		break;
	case MOUSE_PAN:
		orbit.mouseReleasePan();

		break;
	}
}

void Renderer::scrollUp() {
	orbit.zoomIn();
}

void Renderer::scrollDown() {
	orbit.zoomOut();
}

void Renderer::loadScene(const Scene *scene) {
	models.clear();

	for(auto agent : scene->getAgents()) {
		AgentModel modeller(agent, RadiusSampler(0.15f), randomizer);

		models.push_back(modeller.getBranches());
	}

	models.push_back(std::shared_ptr<Model>(new Model(
	{
		Vertex(Vector(-10, 0, -10), Vector(0, 1, 0), Vector(1, 0, 0)),
		Vertex(Vector(10, 0, -10), Vector(0, 1, 0), Vector(0, 1, 0)),
		Vertex(Vector(10, 0, 10), Vector(0, 1, 0), Vector(0, 0, 1)),
		Vertex(Vector(-10, 0, 10), Vector(0, 1, 0), Vector(1, 1, 1))
	},
	{
		0, 2, 1, 2, 0, 3
	}
	)));
}

void Renderer::updateUniforms() {
	uniforms.setProjection(orbit.getMatrix() * projection);
	uniforms.update();
}

void Renderer::updateProjection() {
	projection = Matrix::makePerspective(
		PROJECTION_ANGLE,
		aspect,
		Z_NEAR,
		Z_FAR);
}