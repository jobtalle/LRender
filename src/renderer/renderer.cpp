#include "renderer.h"
#include "glad/glad.h"
#include "math/constants.h"
#include "renderer/passes/renderPassView.h"

#include <math.h>

using namespace LRender;

const float Renderer::PROJECTION_ANGLE = Constants::PI * 0.25f;
const float Renderer::Z_NEAR = 0.05f;
const float Renderer::Z_FAR = 400;
const Vector Renderer::CLEAR_COLOR = Vector(0.3f, 0.4f, 0.6f);

Renderer::Renderer(const size_t width, const size_t height) :
	renderPass(new RenderPassView()) {
	glEnable(GL_DEPTH_TEST);
	glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, 1);

	setSize(width, height);
	updateProjection();
}

void Renderer::setScene(
	std::shared_ptr<Scene> scene,
	std::function<void(Report&)> callback) {
	std::lock_guard<std::mutex> lock(access);

	renderTasks.push_back(RenderTask(scene, callback));
}

void Renderer::update() {
	std::lock_guard<std::mutex> lock(access);

	if(!renderTasks.empty()) {
		Report report;
		auto task = *renderTasks.begin();

		renderTasks.erase(renderTasks.begin());

		loadScene(task.scene.get(), report);

		task.report(report);
	}
}

void Renderer::render() {
	if(renderPass)
		renderPass->render(shaders, orbit, projection, terrains, agents);
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

void Renderer::loadScene(const Scene *scene, Report &report) {
	terrains.clear();
	agents.clear();

	terrains.push_back(TerrainModel(scene->getTerrain()));

	for(auto &agent : scene->getAgents()) {
		agents.push_back(AgentModel(agent, randomizer));

		auto model = --agents.end();
		
		report.add(ReportAgent(
			ReportLimits(model->getMinimum(), model->getMaximum()),
			ReportArea(model->getArea())
		));
	}

	if(agents.size() == 1)
		orbit.setFocus(agents[0].getMinimum() + (agents[0].getMaximum() - agents[0].getMinimum()) * 0.5f);
}

void Renderer::updateProjection() {
	projection = Matrix::makePerspective(
		PROJECTION_ANGLE,
		aspect,
		Z_NEAR,
		Z_FAR);
}

Renderer::RenderTask::RenderTask(
	std::shared_ptr<Scene> scene,
	std::function<void(Report&)> report) :
	scene(scene),
	report(report) {

}