#include "standardLeaf.h"
#include "math/area.h"

using namespace LRender;

const Vector Shape::StandardLeaf::NORMAL = Vector(0, 0, -1);

float Shape::StandardLeaf::modelA(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const float fertility,
	const Vector &position,
	const Quaternion &orientation) {
	auto shape = makeShape();

	for(auto &vector : shape) {
		indices.push_back(vertices.size());
		vertices.emplace_back(
			orientation * vector + position,
			orientation * NORMAL,
			fertility,
			0.0f);
	}

	return Area::triangle(shape[0], shape[1], shape[2]);
}

std::vector<Vector> Shape::StandardLeaf::makeShape() {
	std::vector<Vector> shape;

	shape.emplace_back(0.0f, 0.0f, 0.0f);
	shape.emplace_back(-0.1f, 0.2f, 0.0f);
	shape.emplace_back(0.1f, 0.2f, 0.0f);

	return shape;
}
