#include "modeller.h"
#include "../math/constants.h"
#include "../math/matrix.h"

#include <math.h>

using namespace LRender;

float getRadius(size_t dist) {
	return (1.0f - (1.0f / (float(dist) / 150.0f + 1.0f))) * 0.1f;
}

void Modeller::makeTube(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const size_t precision,
	const Path &path) {
	std::vector<Vector> ring;
	Vector color(0.5, 0.7, 0.2);
	size_t offset = path.isChild() ? 2 : 0;

	for(size_t i = 0; i < precision; ++i) {
		const float radians = Constants::PI * 2 * float(i) / precision;

		ring.push_back(Vector(cos(radians), 0, sin(radians)));
	}

	for(auto node = path.getNodes().begin() + offset; node < path.getNodes().end(); ++node) {
		const float radius = getRadius(node->topDist);
		const Quaternion qa = node->getHeading();
		const Quaternion qb = (node == path.getNodes().end() - 1 || (node == path.getNodes().begin() && path.isAnchor())) ? qa : (node + 1)->getHeading();

		for(auto ringPoint : ring) {
			const Vector normal(((qa * ringPoint + qb * ringPoint) * 0.5).normalize());

			vertices.push_back(Vertex(node->position + normal * radius, normal, color));
		}

		const size_t size = vertices.size();

		if(node > path.getNodes().begin() + offset) for(size_t i = 0; i < precision; ++i) {
			indices.push_back(size - 1 - i);
			indices.push_back(size - 1 - precision - i);
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - ((i + 1) % precision));
			indices.push_back(size - 1 - i);
		}
	}
}