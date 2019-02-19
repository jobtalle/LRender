#include "renderer.h"
#include "modeller/modeller.h"
#include "glad/glad.h"

#include <math.h>

using namespace LRender;

const std::string Renderer::FILE_SHADER_VERTEX_GEOMETRY = "glsl/vertexGeometry.glsl";
const std::string Renderer::FILE_SHADER_FRAGMENT_GEOMETRY = "glsl/fragmentGeometry.glsl";
const float Renderer::PITCH_MIN = 0.1f;
const float Renderer::PITCH_MAX = atan(1) * 2 - Renderer::PITCH_MIN;
const float Renderer::RADIANS_PER_PIXEL = 0.005f;
const float Renderer::PROJECTION_ANGLE = atan(1) * 1.5f;
const float Renderer::Z_NEAR = 0.01f;
const float Renderer::Z_FAR = 600;

Renderer::Renderer(const size_t width, const size_t height) :
	dragging(false),
	viewAngle(atan(1)),
	viewPitch(viewAngle) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shaderGeometry.reset(new Shader(FILE_SHADER_VERTEX_GEOMETRY, FILE_SHADER_FRAGMENT_GEOMETRY));
	shader = shaderGeometry.get();

	setSize(width, height);
	updateProjection();
	updateView();
}

void Renderer::setScene(std::shared_ptr<Scene> scene) {
	std::lock_guard<std::mutex> lock(access);

	nextScene = scene;
}

void Renderer::update() {
	std::lock_guard<std::mutex> lock(access);

	if(nextScene) {
		loadScene(nextScene.get());

		nextScene.reset();
	}
}

void Renderer::render() const {
	uniforms.update();
	shader->use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto model : models)
		model->draw();
}

void Renderer::setSize(const size_t width, const size_t height) {
	glViewport(0, 0, width, height);

	aspect = float(width) / height;

	updateProjection();
}

void Renderer::mouseMove(const size_t x, const size_t y) {
	if(dragging) {
		const int dx = int(x) - mouseX;
		const int dy = int(y) - mouseY;

		viewAngle += dx * RADIANS_PER_PIXEL;
		viewPitch += dy * RADIANS_PER_PIXEL;

		if(viewPitch < PITCH_MIN)
			viewPitch = PITCH_MIN;
		else if(viewPitch > PITCH_MAX)
			viewPitch = PITCH_MAX;

		updateView();
	}

	mouseX = x;
	mouseY = y;
}

void Renderer::mousePress() {
	dragging = true;
}

void Renderer::mouseRelease() {
	dragging = false;
}

void Renderer::loadScene(const Scene *scene) {
	models.clear();

	for(auto agent : scene->getAgents()) {
		Modeller modeller(agent);

		models.push_back(modeller.getBranches());
	}

	models.push_back(std::shared_ptr<Model>(new Model(
	{
		Vertex(Vector(-1, 0, -1), Vector(1, 0, 0)),
		Vertex(Vector(1, 0, -1), Vector(0, 1, 0)),
		Vertex(Vector(1, 0, 1), Vector(0, 0, 1)),
		Vertex(Vector(-1, 0, 1), Vector(1, 1, 1))
	},
	{
		0, 2, 1, 2, 0, 3
	}
	)));
}

void Renderer::updateUniforms() {
	uniforms.setProjection(view * projection);
}

void Renderer::updateProjection() {
	projection = Matrix::makePerspective(
		PROJECTION_ANGLE,
		aspect,
		Z_NEAR,
		Z_FAR);

	updateUniforms();
}

void Renderer::updateView() {
	view = Matrix::makeLookAt(
		Vector(
			cos(viewAngle) * cos(viewPitch),
			sin(viewPitch),
			sin(viewAngle) * cos(viewPitch)) * 2,
		Vector(
			0,
			0,
			0),
		Vector(
			0,
			1,
			0));

	updateUniforms();
}