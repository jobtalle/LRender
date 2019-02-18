#include "model.h"

using namespace LRender;

Model::Model(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices) {
	createBuffers();
	upload(vertices, indices);
}

Model::~Model() {
	freeBuffers();
}

void Model::draw() const {

}

void Model::createBuffers() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(BUFFER_COUNT, buffers);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUFFER_VERTICES]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BUFFER_INDICES]);
	glBindVertexArray(0);
}

void Model::upload(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices) {
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUFFER_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BUFFER_INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void Model::freeBuffers() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(BUFFER_COUNT, buffers);
}