#include "renderer.h"
#include "modeller/radiusSampler.h"
#include "glad/glad.h"

#include <math.h>

using namespace LRender;

const float Renderer::PROJECTION_ANGLE = atan(1) * 1.5f;
const float Renderer::Z_NEAR = 0.05f;
const float Renderer::Z_FAR = 400;

Renderer::Renderer(const size_t width, const size_t height) {
	glEnable(GL_DEPTH_TEST);

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
	uniforms.setProjection(orbit.getMatrix() * projection);
	uniforms.update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	shaders.getBranches().use();

	for(auto &terrain : terrains)
		terrain.getModel().draw();

	for(auto &agent : agents)
		agent.getBranches().draw();

	glDisable(GL_CULL_FACE);

	shaders.getLeaves().use();

	for(auto &agent : agents)
		agent.getLeaves().draw();
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
	terrains.clear();
	agents.clear();

	terrains.push_back(TerrainModel(scene->getTerrain()));

	for(auto &agent : scene->getAgents())
		agents.push_back(AgentModel(agent, RadiusSampler(1.1f), randomizer));
}

void Renderer::updateProjection() {
	projection = Matrix::makePerspective(
		PROJECTION_ANGLE,
		aspect,
		Z_NEAR,
		Z_FAR);
}