#include "branch.h"
#include "math/constants.h"

#include <cmath>

using namespace LRender;

void Shape::Branch::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const RadiusSampler &radiusSampler,
	const float fertility,
	const size_t precision,
	const LRender::Branch &branch) {
	const auto ring = makeRing(precision);

	for(auto node = branch.getNodes().begin(); node < branch.getNodes().end(); ++node) {
		auto transformedRing = ring;

		branch.transform(transformedRing, node);

		for(auto &ringPoint : transformedRing)
			vertices.emplace_back(Vertex(
				node->position + ringPoint * radiusSampler.sampleRadius(node->topDist),
				ringPoint,
				radiusSampler.sampleFactor(node->topDist), 
				fertility));

		const auto size = vertices.size();

		if(node > branch.getNodes().begin()) for(size_t i = 0; i < precision; ++i) {
			indices.push_back(static_cast<uint32_t>(size - 1 - i));
			indices.push_back(static_cast<uint32_t>(size - 1 - precision - i));
			indices.push_back(static_cast<uint32_t>(size - 1 - precision - ((i + 1) % precision)));
			indices.push_back(static_cast<uint32_t>(size - 1 - precision - ((i + 1) % precision)));
			indices.push_back(static_cast<uint32_t>(size - 1 - ((i + 1) % precision)));
			indices.push_back(static_cast<uint32_t>(size - 1 - i));
		}
	}
}

std::vector<Vector> Shape::Branch::makeRing(const size_t precision) {
	std::vector<Vector> ring;

	for(size_t i = 0; i < precision; ++i) {
		const auto radians = Constants::PI * 2 * float(i) / precision;

		ring.emplace_back(Vector(std::cos(radians), 0, std::sin(radians)));
	}

	return ring;
}
