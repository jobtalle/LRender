#include "tube.h"
#include "../math/constants.h"

#include <math.h>

using namespace LRender;

void Tube::modelTube(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &color,
	const RadiusSampler &radiusSampler,
	const size_t precision,
	const Branch &branch) {
	const std::vector<Vector> ring(makeRing(precision));

	for(auto node = branch.getNodes().begin(); node < branch.getNodes().end(); ++node) {
		std::vector<Vector> transformedRing = ring;

		branch.transform(transformedRing, node);

		for(auto &ringPoint : transformedRing)
			vertices.push_back(Vertex(
				node->position + ringPoint * radiusSampler.sample(node->topDist),
				ringPoint,
				color));

		const size_t size = vertices.size();

		if(node > branch.getNodes().begin()) for(size_t i = 0; i < precision; ++i) {
			indices.push_back(size - 1 - i);
			indices.push_back(size - 1 - precision - i);
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - ((i + 1) % precision));
			indices.push_back(size - 1 - i);
		}
	}
}

std::vector<Vector> Tube::makeRing(const size_t precision) {
	std::vector<Vector> ring;

	for(size_t i = 0; i < precision; ++i) {
		const float radians = Constants::PI * 2 * float(i) / precision;

		ring.push_back(Vector(cos(radians), 0, sin(radians)));
	}

	return ring;
}