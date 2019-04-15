#include "renderPassMasks.h"

using namespace LRender;

RenderPassMasks::RenderPassMasks(const size_t width, const size_t height) :
	target(std::make_shared<RenderTargetUint>(width, height)) {
	
}

short RenderPassMasks::sample(const float x, const float y) const {
	target->download();

	return target->sample(x, y);
}

void RenderPassMasks::render(
	const Shaders &shaders,
	const Orbit &orbit,
	const Matrix &projection,
	const std::vector<TerrainModel> &terrains,
	const std::vector<AgentModel> &agents,
	const Renderer *renderer) {
	uniforms.setProjection(orbit.getMatrix() * projection);
	uniforms.update();

	target->clear();
	target->bind();

	shaders.getExposure().use();

	glEnable(GL_CULL_FACE);

	for(size_t agent = 0; agent < agents.size(); ++agent) {
		shaders.getExposure().setAgent(agent);

		agents[agent].getBranches().draw();
	}

	glDisable(GL_CULL_FACE);

	for(size_t agent = 0; agent < agents.size(); ++agent) {
		shaders.getExposure().setAgent(agent);

		agents[agent].getLeaves().draw();
	}
}
