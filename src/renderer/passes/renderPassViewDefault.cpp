#include "renderPassViewDefault.h"
#include "renderer/renderer.h"
#include "glad/glad.h"
#include "renderPassImage.h"

using namespace LRender;

const Vector RenderPassViewDefault::CLEAR_COLOR = Vector(0.3f, 0.4f, 0.6f);
const size_t RenderPassViewDefault::SHADOW_SIZE = 4096;
const float RenderPassViewDefault::LIGHT_DISTANCE = 16;
const float RenderPassViewDefault::LIGHT_ZNEAR = -10;
const float RenderPassViewDefault::LIGHT_ZFAR = 20;
const Vector RenderPassViewDefault::UP = Vector(0, 1, 0);

RenderPassViewDefault::RenderPassViewDefault() :
	shadowTarget(SHADOW_SIZE, SHADOW_SIZE) {
	lightDirection = Vector(-1, 2, -1).normalize();

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
	const auto lightProjection = Matrix::makeOrtho(
		-10, 
		-10, 
		10, 
		10, 
		LIGHT_ZNEAR,
		LIGHT_ZFAR);
	const auto lightView = Matrix::makeLookAt(
		lightDirection,
		Vector(),
		UP);

	shadowTarget.bind();

	glClear(GL_DEPTH_BUFFER_BIT);

	uniformsShadows.setProjection(lightProjection * lightView);
	uniformsShadows.update();

	shaders.getShadows().use();

	glEnable(GL_CULL_FACE);

	for(auto &agent : agents)
		agent.getBranches().draw();

	glDisable(GL_CULL_FACE);

	for(auto &terrain : terrains)
		terrain.getModel().draw();

	for(auto &agent : agents)
		agent.getLeaves().draw();

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
		
	shaders.getBranches().use();

	for(auto &agent : agents)
		agent.getBranches().draw();

	glDisable(GL_CULL_FACE);

	shaders.getLeaves().use();

	for(auto &agent : agents)
		agent.getLeaves().draw();
}