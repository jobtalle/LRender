#include "renderPassViewDefault.h"
#include "glad/glad.h"

using namespace LRender;

const Vector RenderPassViewDefault::CLEAR_COLOR = Vector(0.3f, 0.4f, 0.6f);

void RenderPassViewDefault::render(
	const Shaders &shaders,
	const Orbit &orbit,
	const Matrix &projection,
	const std::vector<TerrainModel> &terrains,
	const std::vector<AgentModel> &agents) {
	uniforms.setProjection(orbit.getMatrix() * projection);
	uniforms.update();

	glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, 1);
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