#include "modeller.h"
#include "../math/constants.h"
#include "../math/matrix.h"

#include <math.h>
#include <iostream>

using namespace LRender;

void Modeller::makeTube(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const size_t precision,
	const std::vector<Node> path) {
	std::vector<Vector> ring;
	Vector color(0.5, 0.7, 0.2);

	for(size_t i = 0; i < precision; ++i) {
		const float radians = Constants::PI * 2 * float(i) / precision;

		ring.push_back(Vector(cos(-radians), 0, sin(-radians)) * 0.02f);
	}

	for(auto node = path.begin(); node < path.end(); ++node) {
		for(auto ringPoint : ring)
			vertices.push_back(Vertex(node->position + node->heading * ringPoint, color));

		const size_t size = vertices.size();

		if(node != path.begin()) for(size_t i = 0; i < precision; ++i) {
			indices.push_back(size - 1 - i);
			indices.push_back(size - 1 - precision - i);
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - ((i + 1) % precision));
			indices.push_back(size - 1 - i);
		}
	}
}