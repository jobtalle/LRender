#include "seed.h"
#include "modeller/shapes/icosphere.h"

using namespace LRender;

void Shape::Seed::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &color,
	const LRender::Seed &seed) {
	Shape::Icosphere::model(
		vertices,
		indices,
		color,
		seed.getPosition(),
		Quaternion(),
		0.3f,
		0);
}