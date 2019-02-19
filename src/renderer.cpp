#include "renderer.h"
#include "modeller/modeller.h"

#include <math.h>

using namespace LRender;

const std::string Renderer::FILE_SHADER_VERTEX_GEOMETRY = "glsl/vertexGeometry.glsl";
const std::string Renderer::FILE_SHADER_FRAGMENT_GEOMETRY = "glsl/fragmentGeometry.glsl";
const float Renderer::PROJECTION_ANGLE = atan(1) * 1.5f;
const float Renderer::Z_NEAR = 0.01f;
const float Renderer::Z_FAR = 600;

bool Renderer::initialized = false;

Renderer::Renderer(const size_t width, const size_t height) {
	if(!initialized)
		initializeGL();

	glGenBuffers(1, &ubo);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

	shaderGeometry.reset(new Shader(FILE_SHADER_VERTEX_GEOMETRY, FILE_SHADER_FRAGMENT_GEOMETRY));
	shader = shaderGeometry.get();

	setSize(width, height);
	updateProjection();

	view = Matrix::makeLookAt(Vector(0, 1, 1) * 3, Vector(0, 0, 0), Vector(0, 1, 0));
}

Renderer::~Renderer() {
	glDeleteBuffers(1, &ubo);
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
	updateUBO();
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

void Renderer::initializeGL() {
	gladLoadGL();

	initialized = true;
}

void Renderer::loadScene(const Scene *scene) {
	models.clear();

	models.push_back(std::shared_ptr<Model>(new Model(
	{
		Vertex(Vector(-1, 0, -1), Vector(1, 0, 0)),
		Vertex(Vector(1, 0, -1), Vector(0, 1, 0)),
		Vertex(Vector(1, 0, 1), Vector(0, 0, 1)),
		Vertex(Vector(-1, 0, 1), Vector(1, 1, 1))
	},
	{
		0, 1, 2, 2, 3, 0, 0, 2, 1, 2, 0, 3
	}
	)));

	for(auto agent : scene->getAgents()) {
		Modeller modeller(agent);

		models.push_back(modeller.getBranches());
	}
}

void Renderer::updateUBO() const {
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Matrix), &(view * projection), GL_DYNAMIC_DRAW);
}

void Renderer::updateProjection() {
	projection = Matrix::makePerspective(
		PROJECTION_ANGLE,
		aspect,
		Z_NEAR,
		Z_FAR);
}