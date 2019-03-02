#include "uniforms.h"

using namespace LRender;

Uniforms::Uniforms() {
	glGenBuffers(1, &ubo);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
}

Uniforms::~Uniforms() {
	glDeleteBuffers(1, &ubo);
}

void Uniforms::update() const {
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(payload), &payload, GL_DYNAMIC_DRAW);
}

void Uniforms::setProjection(const Matrix &projection) {
	payload.projection = projection;
}