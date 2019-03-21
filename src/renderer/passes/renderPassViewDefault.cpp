#include "renderPassViewDefault.h"
#include "renderer/renderer.h"
#include "glad/glad.h"
#include "renderPassImage.h"

using namespace LRender;

const Vector RenderPassViewDefault::CLEAR_COLOR = Vector(0.3f, 0.4f, 0.6f);
const size_t RenderPassViewDefault::SHADOW_SIZE = 4096;

RenderPassViewDefault::RenderPassViewDefault() :
	shadowTarget(SHADOW_SIZE, SHADOW_SIZE) {
	lightDirection = Vector(1, -0.5f , 1).normalize();
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
	
	for(auto &terrain : terrains)
		terrain.getModel().draw();

	for(auto &agent : agents)
		agent.getBranches().draw();

	glDisable(GL_CULL_FACE);

	shaders.getLeavesShadows().use();
	shaders.getLeavesShadows().setShadowMap(shadowTarget.getDepth());

	for(auto &agent : agents)
		agent.getLeaves().draw();
}