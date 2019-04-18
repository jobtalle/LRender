#include "renderer.h"
#include "glad/glad.h"
#include "math/constants.h"
#include "renderer/passes/renderPassViewDefault.h"
#include "renderer/passes/renderPassViewWireframe.h"
#include "renderer/passes/renderPassMasks.h"
#include "renderer/tasks/task.h"
#include "passes/renderPassArea.h"
#include "tasks/taskSelect.h"

using namespace LRender;

const float Renderer::PROJECTION_ANGLE = Constants::PI * 0.25f;
const float Renderer::Z_NEAR = 0.05f;
const float Renderer::Z_FAR = 400;

// OpenGL debugging:
#include <iostream>

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if(type != GL_DEBUG_TYPE_ERROR)
		return;

	std::cout << message << std::endl;
}
//

Renderer::Renderer(const size_t width, const size_t height) :
	mouseX(0),
	mouseY(0),
	updatePass(std::make_shared<RenderPassViewDefault>()) {
	glEnable(GL_DEPTH_TEST);

	// OpenGL debugging:
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	//

	setSize(width, height);
	updateProjection();
}

void Renderer::enqueue(const std::shared_ptr<Task>& task) {
	std::lock_guard<std::mutex> lock(access);

	tasks.push_back(task);
}

void Renderer::update() {
	std::lock_guard<std::mutex> lock(access);

	for(auto &task : tasks)
		task->perform(*this);

	tasks.clear();
}

void Renderer::bindDefault() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);
}

void Renderer::render() const {
	render(*updatePass);
}

void Renderer::render(RenderPass &pass) const {
	pass.render(shaders, orbit, projection, terrains, agents, this);
}

void Renderer::center() {
	orbit.setFocus(sceneCenter);
}

void Renderer::focus() {
	if(selected == -1)
		return;

	const auto focus = agents[selected].getMinimum() + (agents[selected].getMaximum() - agents[selected].getMinimum()) * 0.5f;

	orbit.setFocus(focus);
}

void Renderer::setSize(const size_t width, const size_t height) {
	this->width = width;
	this->height = height;

	aspect = float(width) / height;

	updateProjection();
}

void Renderer::mouseMove(const size_t x, const size_t y) {
	orbit.mouseMove(x, y);

	mouseX = x;
	mouseY = y;
	mouseMoved = true;
}

void Renderer::mousePress(const MouseButton button) {
	mouseMoved = false;

	switch(button) {
	case DRAG:
		orbit.mouseGrabDrag();

		break;
	case PAN:
		orbit.mouseGrabPan();
		
		break;
	}
}

void Renderer::mouseRelease(const MouseButton button) {
	if(!mouseMoved)
		enqueue(std::make_shared<Task::Select>(
			static_cast<float>(mouseX) / width,
			static_cast<float>(mouseY) / height));

	switch(button) {
	case DRAG:
		orbit.mouseReleaseDrag();

		break;
	case PAN:
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

void Renderer::setSelected(int selected) {
	this->selected = selected;
}

int Renderer::getSelected() const {
	return selected;
}

size_t Renderer::getWidth() const {
	return width;
}

size_t Renderer::getHeight() const {
	return height;
}

void Renderer::setMode(const Mode mode) {
	switch(mode) {
	case DEFAULT:
		setPass(std::make_shared<RenderPassViewDefault>());

		break;
	case WIREFRAME:
		setPass(std::make_shared<RenderPassViewWireframe>());

		break;
	}
}

void Renderer::setPass(const std::shared_ptr<RenderPass> &pass) {
	updatePass = pass;
}

void Renderer::loadScene(const Scene *scene, LParse::Randomizer &randomizer, Report *report) {
	setSelected(-1);

	terrains.clear();
	agents.clear();

	terrains.emplace_back(scene->getTerrain());

	for(auto &agent : scene->getAgents()) {
		agents.emplace_back(agent, randomizer);

		if(report) {
			const auto model = --agents.end();
			std::vector<ReportSeed> seedReports;
			std::vector<ReportLeaf> leafReports;

			for(const auto &seedPosition : model->getSeedPositions())
				seedReports.emplace_back(seedPosition);

			for(const auto &leafArea : model->getLeafAreas())
				leafReports.emplace_back(leafArea);

			report->add(ReportAgent(
				seedReports,
				leafReports,
				ReportLimits(model->getMinimum(), model->getMaximum()),
				ReportSize(agent.getSymbols().size())
			));
		}
	}

	sceneCenter.x = scene->getTerrain().getWidth() * 0.5f;
	sceneCenter.z = scene->getTerrain().getHeight() * 0.5f;

	if(report && report->hasLimits())
		sceneCenter.y = report->getLimits().getMinimum().y +
			(report->getLimits().getMaximum().y - report->getLimits().getMinimum().y) * 0.5f;
	else
		sceneCenter.y = 0;
}

void Renderer::updateProjection() {
	projection = Matrix::makePerspective(
		PROJECTION_ANGLE,
		aspect,
		Z_NEAR,
		Z_FAR);
}
