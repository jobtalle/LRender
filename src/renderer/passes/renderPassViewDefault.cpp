#include "renderPassViewDefault.h"
#include "renderer/renderer.h"
#include "glad/glad.h"
#include "renderPassImage.h"

using namespace LRender;

const Vector RenderPassViewDefault::CLEAR_COLOR = Vector(0.3f, 0.4f, 0.6f);
const size_t RenderPassViewDefault::SHADOW_SIZE = 2048;

RenderPassViewDefault::RenderPassViewDefault() :
	shadowTarget(SHADOW_SIZE, SHADOW_SIZE) {
	lightDirection = Vector(1, -1 , 1).normalize();
	shadowPass.setLightDirection(lightDirection);

	uniformsLight.setDirection(lightDirection);
	uniformsLight.setColor(Vector(1, 1, 1));
	uniformsLight.setAmbient(0.2f);
	uniformsLight.setDiffuse(0.8f);
	uniformsLight.update();
}

void RenderPassViewDefault::render(
	const Shaders &shaders,
	const Orbit &orbit,
	const Matrix &projection,
	const std::vector<TerrainModel> &terrains,
	const std::vector<AgentModel> &agents,
	const Renderer *renderer) {
	shadowTarget.bind();
	
	shadowPass.render(shaders, orbit, projection, terrains, agents, renderer);

	renderer->bindDefault();

	uniformsView.setProjection(orbit.getMatrix() * projection);
	uniformsView.update();
	
	glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	shaders.getGeometryShadows().use();
	shaders.getGeometryShadows().setShadowMap(shadowTarget.getDepth());
	shaders.getGeometryShadows().setColors(renderer->getColors().getGround());
	
	for(auto &terrain : terrains)
		terrain.getModel().draw();

	shaders.getGeometryShadows().setColors(renderer->getColors().getBranches());

	for(auto agent = 0; agent < agents.size(); ++agent) {
		if(agent == renderer->getSelected()) {
			shaders.getGeometryShadows().setColors(renderer->getColors().getBranchesSelected());
			agents[agent].getBranches().draw();
			shaders.getGeometryShadows().setColors(renderer->getColors().getBranches());
		}
		else
			agents[agent].getBranches().draw();
	}

	glDisable(GL_CULL_FACE);

	shaders.getLeavesShadows().use();
	shaders.getLeavesShadows().setShadowMap(shadowTarget.getDepth());
	shaders.getLeavesShadows().setColors(renderer->getColors().getLeaves());

	for(auto agent = 0; agent < agents.size(); ++agent) {
		if(agent == renderer->getSelected()) {
			shaders.getLeavesShadows().setColors(renderer->getColors().getLeavesSelected());
			agents[agent].getLeaves().draw();
			shaders.getLeavesShadows().setColors(renderer->getColors().getLeaves());
		}
		else
			agents[agent].getLeaves().draw();
	}
}