#include "renderPassInteger.h"

using namespace LRender;

const std::vector<float> RenderPassInteger::VERTICES = {
	0, 0,
	1, 0,
	1, 1,
	1, 1,
	0, 1,
	0, 0
};

RenderPassInteger::RenderPassInteger(std::shared_ptr<RenderTargetUint> image) :
	image(std::move(image)) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vertices);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VERTICES.size(), VERTICES.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
}

RenderPassInteger::~RenderPassInteger() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vertices);
}

void RenderPassInteger::render(
	const Shaders& shaders,
	const Orbit& orbit,
	const Matrix& projection,
	const std::vector<TerrainModel>& terrains,
	const std::vector<AgentModel>& agents,
	const Renderer *renderer) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaders.getInteger().use();
	shaders.getInteger().setImage(image->getTexture());

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
