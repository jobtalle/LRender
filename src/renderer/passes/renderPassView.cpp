#include "renderPassView.h"
#include "glad/glad.h"

using namespace LRender;

void RenderPassView::render(
	const Shaders &shaders,
	const Orbit &orbit,
	const Matrix &projection,
	const std::vector<LRender::TerrainModel> &terrains,
	const std::vector<LRender::AgentModel> &agents) {
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