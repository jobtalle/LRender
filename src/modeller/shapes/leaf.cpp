#include "leaf.h"
#include "math/area.h"

using namespace LRender;

float Shape::Leaf::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const float fertility,
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
	auto u = fertility;
	auto v = 0.5f;

	vertices.emplace_back(
		a->position,
		((a + 1)->position - a->position).cross((b + 1)->position - b->position).normalize(),
		u, v);

	while(++a, ++b, a < aEnd && b < bEnd) {
		auto na = (a->position - (a - 1)->position).cross(b->position - a->position);
		auto nb = (b->position - (b - 1)->position).cross(b->position - a->position);

		if(a + 1 != aEnd)
			na += ((a + 1)->position - a->position).cross(b->position - a->position);

		if(b + 1 != bEnd)
			nb +=((b + 1)->position - b->position).cross(b->position - a->position);
		
		vertices.emplace_back(a->position, na.normalize(), u, v);
		vertices.emplace_back(b->position, nb.normalize(), u, v);

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
				u, v);

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
				u, v);

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

	return Area::triangle(
		vertices[a].position,
		vertices[b].position,
		vertices[c].position);
}