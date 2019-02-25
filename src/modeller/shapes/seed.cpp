#include "seed.h"
#include "modeller/shapes/icosphere.h"

#include <algorithm>

using namespace LRender;

const float Shape::Seed::RADIUS_FACTOR = 2.0f;
const float Shape::Seed::RADIUS_MIN = 0.2f;

void Shape::Seed::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &color,
	const RadiusSampler &radiusSampler,
	const LRender::Seed &seed) {
	Shape::Icosphere::model(
		vertices,
		indices,
		color,
		seed.getPosition(),
		Quaternion(),
		std::max(radiusSampler.sample(seed.getTopDist()) * RADIUS_FACTOR, RADIUS_MIN),
		1);
}