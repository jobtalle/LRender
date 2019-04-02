#include "renderPassShadows.h"

using namespace LRender;

const Vector RenderPassShadows::UP = Vector(0, 1, 0);
const float RenderPassShadows::RADIUS = 4;

RenderPassShadows::RenderPassShadows() :
	lightProjection(Matrix::makeOrtho(
		-RADIUS,
		-RADIUS,
		RADIUS,
		RADIUS,
		-RADIUS,
		RADIUS)) {
	
}

void RenderPassShadows::setLightDirection(const Vector& direction) {
	lightDirection = direction;
}

void RenderPassShadows::render(
	const Shaders &shaders,
	const Orbit &orbit,
	const Matrix &projection,
	const std::vector<TerrainModel> &terrains,
	const std::vector<AgentModel> &agents,
	const Renderer *renderer) {
	const auto lightView = Matrix::makeLookAt(
		orbit.getFocus() - lightDirection,
		orbit.getFocus(),
		UP);

	glClear(GL_DEPTH_BUFFER_BIT);

	uniforms.setProjection(lightView * lightProjection);
	uniforms.update();

	shaders.getShadows().use();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	for(auto &agent : agents)
		agent.getBranches().draw();

	glCullFace(GL_BACK);

	for(auto &terrain : terrains)
		terrain.getModel().draw();

	glDisable(GL_CULL_FACE);

	for(auto &agent : agents)
		agent.getLeaves().draw();
}
