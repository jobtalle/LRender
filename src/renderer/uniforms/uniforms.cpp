#include "uniforms.h"

using namespace LRender;

Uniforms::Uniforms(const GLuint index) {
	glGenBuffers(1, &ubo);
	glBindBufferBase(GL_UNIFORM_BUFFER, index, ubo);
}

Uniforms::~Uniforms() {
	glDeleteBuffers(1, &ubo);
}

void Uniforms::updateBuffer(const GLsizeiptr payloadSize, const GLvoid *data) const {
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, payloadSize, data, GL_DYNAMIC_DRAW);
}
