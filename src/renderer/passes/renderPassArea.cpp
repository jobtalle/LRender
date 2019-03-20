#include "renderPassArea.h"
#include "renderer/renderer.h"

using namespace LRender;

RenderPassArea::RenderPassArea(const ReportLimits &limits) {
	makeViewport(limits);
}

float RenderPassArea::getViewportWidth() const {
	return viewport.width;
}

float RenderPassArea::getViewportHeight() const {
	return viewport.height;
}

void RenderPassArea::setAngle(const float angle) {
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	lookAt = Matrix::makeLookAt(
		center + Vector(
			c * Renderer::Z_FAR * 0.5f,
			s * Renderer::Z_FAR * 0.5f, 
			0),
		center,
		Vector(s, -c, 0));
}

void RenderPassArea::render(
	const Shaders& shaders,
	const Orbit& orbit,
	const Matrix& projection,
	const std::vector<TerrainModel>& terrains,
	const std::vector<AgentModel>& agents,
	const Renderer *renderer) {
	uniforms.setProjection(lookAt * this->projection);
	uniforms.update();

	shaders.getExposure().use();

	glEnable(GL_CULL_FACE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	for(auto &terrain : terrains)
		terrain.getModel().draw();

	for(auto &agent : agents)
		agent.getBranches().draw();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDisable(GL_CULL_FACE);

	for(size_t agent = 0; agent < agents.size(); ++agent) {
		shaders.getExposure().setAgent(agent);

		agents[agent].getLeaves().draw();
	}
}

void RenderPassArea::makeViewport(const ReportLimits& limits) {
	center = limits.getMinimum() + (limits.getMaximum() - limits.getMinimum()) * 0.5f;

	const float dx = limits.getMinimum().x - center.x;
	const float dy = limits.getMinimum().y - center.y;

	viewport.width = limits.getMaximum().z - limits.getMinimum().z;
	viewport.height = std::sqrt(dx * dx + dy * dy) * 2;

	projection = Matrix::makeOrtho(
		-viewport.width * 0.5f, 
		-viewport.height * 0.5f,
		viewport.width * 0.5f,
		viewport.height * 0.5f,
		Renderer::Z_NEAR,
		Renderer::Z_FAR);
}
