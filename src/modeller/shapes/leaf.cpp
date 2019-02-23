#include "leaf.h"

#include <math.h>

using namespace LRender;
#include <iostream>
float Shape::Leaf::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &color,
	std::vector<Node>::const_iterator a,
	std::vector<Node>::const_iterator aEnd,
	std::vector<Node>::const_iterator b,
	std::vector<Node>::const_iterator bEnd) {
	float area = 0;
	auto verticesFirst = vertices.size() - 1;
	auto verticesSize = (aEnd - a) + (bEnd - b) + 2;
	const auto nBase = ((a + 1)->position - a->position).cross((b + 1)->position - b->position).normalize();

	vertices.push_back(Vertex(a->position, nBase, color));
	vertices.push_back(Vertex(b->position, nBase, color));

	while(++a, ++b, a < aEnd && b < bEnd) {
		auto na = (a->position - (a - 1)->position).cross(b->position - a->position);
		auto nb = (b->position - (b - 1)->position).cross(b->position - a->position);

		if(a + 1 != aEnd)
			na += ((a + 1)->position - a->position).cross(b->position - a->position);

		if(b + 1 != bEnd)
			nb +=((b + 1)->position - b->position).cross(b->position - a->position);
		
		vertices.push_back(Vertex(a->position, na.normalize(), color));
		vertices.push_back(Vertex(b->position, nb.normalize(), color));

		indices.push_back(vertices.size() - 2);
		indices.push_back(vertices.size() - 1);
		indices.push_back(vertices.size() - 3);
		indices.push_back(vertices.size() - 3);
		indices.push_back(vertices.size() - 4);
		indices.push_back(vertices.size() - 2);
	}

	if(a != aEnd) {
		--a; --b;

		const size_t anchor = vertices.size() - 1;
		size_t previous = vertices.size() - 2;

		while(++a < aEnd) {
			auto n = (a->position - (a - 1)->position).cross(b->position - a->position);

			if(a + 1 != aEnd)
				n += ((a + 1)->position - a->position).cross(b->position - a->position);

			vertices.push_back(Vertex(
				a->position,
				n.normalize(),
				color));

			indices.push_back(anchor);
			indices.push_back(previous);
			indices.push_back(vertices.size() - 1);

			previous = vertices.size() - 1;

		}
	}
	else if(b != bEnd) {
		--a, --b;

		const size_t anchor = vertices.size() - 2;
		size_t previous = vertices.size() - 1;

		while(++b < bEnd) {
			auto n = (b->position - (b - 1)->position).cross(b->position - a->position);

			if(b + 1 != bEnd)
				n += ((b + 1)->position - b->position).cross(b->position - a->position);

			vertices.push_back(Vertex(
				b->position,
				n.normalize(),
				color));

			indices.push_back(anchor);
			indices.push_back(previous);
			indices.push_back(vertices.size() - 1);

			previous = vertices.size() - 1;
		}
	}

	return area;
}

float Shape::Leaf::area(
	const Vector &a,
	const Vector &b,
	const Vector &c) {
	const float la = (b - a).length();
	const float lb = (b - c).length();
	const float lc = (a - c).length();
	const float p = (la + lb + lc) * 0.5f;

	return sqrt(p * (p - la) * (p - lb) * (p - lc));
}