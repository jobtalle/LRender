#include "renderPassViewWireframe.h"

using namespace LRender;

const Vector RenderPassViewWireframe::CLEAR_COLOR = Vector(0.3f, 0.3f, 0.3f);

void RenderPassViewWireframe::render(
	const Shaders &shaders,
	const Orbit &orbit,
	const Matrix &projection,
	const std::vector<TerrainModel> &terrains,
	const std::vector<AgentModel> &agents,
	const Renderer *renderer) {
	uniforms.setProjection(orbit.getMatrix() * projection);
	uniforms.update();

	glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	shaders.getBranches().use();

	for(auto &terrain : terrains)
		terrain.getModel().draw(true);

	for(auto &agent : agents)
		agent.getBranches().draw(true);

	glDisable(GL_CULL_FACE);

	shaders.getLeaves().use();

	for(auto &agent : agents)
		agent.getLeaves().draw(true);
}