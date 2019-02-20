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
	const std::vector<Vector> path) {
	std::vector<Vector> ring;
	Vector color(0.5, 0.7, 0.2);

	for(size_t i = 0; i < precision; ++i) {
		const float radians = Constants::PI * 2 * float(i) / precision;

		ring.push_back(Vector(cos(-radians), 0, sin(-radians)) * 0.02f);
	}

	std::vector<Vector>::const_iterator previous = path.begin();

	for(auto point = path.begin(); point < path.end(); ++point) {
		const Vector delta = (point == previous ? *point - *(point + 1) : *previous - *point).normalize();
		const Matrix direction = Matrix::makeDirection(delta, Vector(0, 0, 1));

		for(auto ringPoint : ring) {
			if(delta.cross(UP).length() > 0)
				vertices.push_back(Vertex(direction * ringPoint + *point, color));
			else
				vertices.push_back(Vertex(ringPoint + *point, color));
		}

		const size_t size = vertices.size();

		if(point != path.begin()) for(size_t i = 0; i < precision; ++i) {
			indices.push_back(size - 1 - i);
			indices.push_back(size - 1 - precision - i);
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - precision - ((i + 1) % precision));
			indices.push_back(size - 1 - ((i + 1) % precision));
			indices.push_back(size - 1 - i);
		}

		previous = point;
	}
}