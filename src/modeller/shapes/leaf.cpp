#include "leaf.h"

using namespace LRender;

float Shape::Leaf::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &color,
	std::vector<Node>::const_iterator a,
	const std::vector<Node>::const_iterator &aEnd,
	std::vector<Node>::const_iterator b,
	const std::vector<Node>::const_iterator &bEnd) {
	while(a + 1 != aEnd && b + 1 != bEnd && (a + 1)->position == (b + 1)->position)
		++a, ++b;

	if(a + 1 == aEnd || b + 1 == bEnd)
		return 0;

	float area = 0;
	auto even = false;
	auto first = true;

	vertices.emplace_back(
		a->position,
		((a + 1)->position - a->position).cross((b + 1)->position - b->position).normalize(),
		color);

	while(++a, ++b, a < aEnd && b < bEnd) {
		auto na = (a->position - (a - 1)->position).cross(b->position - a->position);
		auto nb = (b->position - (b - 1)->position).cross(b->position - a->position);

		if(a + 1 != aEnd)
			na += ((a + 1)->position - a->position).cross(b->position - a->position);

		if(b + 1 != bEnd)
			nb +=((b + 1)->position - b->position).cross(b->position - a->position);
		
		vertices.emplace_back(a->position, na.normalize(), color);
		vertices.emplace_back(b->position, nb.normalize(), color);

		if(first) {
			area += addTriangle(vertices, indices, vertices.size() - 2, vertices.size() - 1, vertices.size() - 3);

			first = false;
		}
		else {
			if(even) {
				area += addTriangle(vertices, indices, vertices.size() - 2, vertices.size() - 1, vertices.size() - 3);
				area += addTriangle(vertices, indices, vertices.size() - 3, vertices.size() - 4, vertices.size() - 2);
			}
			else {
				area += addTriangle(vertices, indices, vertices.size() - 1, vertices.size() - 3, vertices.size() - 4);
				area += addTriangle(vertices, indices, vertices.size() - 4, vertices.size() - 2, vertices.size() - 1);
			}
		}

		even = !even;
	}

	if(a != aEnd) {
		--a; --b;

		const auto anchor = vertices.size() - 1;
		auto previous = vertices.size() - 2;

		while(++a < aEnd) {
			auto n = (a->position - (a - 1)->position).cross(b->position - a->position);

			if(a + 1 != aEnd)
				n += ((a + 1)->position - a->position).cross(b->position - a->position);

			vertices.emplace_back(
				a->position,
				n.normalize(),
				color);

			area += addTriangle(vertices, indices, anchor, previous, vertices.size() - 1);

			previous = vertices.size() - 1;
		}
	}
	else if(b != bEnd) {
		--a, --b;

		const auto anchor = vertices.size() - 2;
		auto previous = vertices.size() - 1;

		while(++b < bEnd) {
			auto n = (b->position - (b - 1)->position).cross(b->position - a->position);

			if(b + 1 != bEnd)
				n += ((b + 1)->position - b->position).cross(b->position - a->position);

			vertices.emplace_back(
				b->position,
				n.normalize(),
				color);

			area += addTriangle(vertices, indices, anchor, previous, vertices.size() - 1);

			previous = vertices.size() - 1;
		}
	}

	return area;
}

float Shape::Leaf::addTriangle(
	const std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const uint32_t a,
	const uint32_t b,
	const uint32_t c) {
	indices.push_back(a);
	indices.push_back(b);
	indices.push_back(c);

	return calculateArea(
		vertices[a].position,
		vertices[b].position,
		vertices[c].position);
}

float Shape::Leaf::calculateArea(
	const Vector &a,
	const Vector &b,
	const Vector &c) {
	const auto la = (b - a).length();
	const auto lb = (b - c).length();
	const auto lc = (a - c).length();
	const auto p = (la + lb + lc) * 0.5f;
	const auto x = p * (p - la) * (p - lb) * (p - lc);

	if(x < 0)
		return 0;

	return sqrt(x);
}
