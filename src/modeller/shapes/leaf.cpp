#include "leaf.h"

#include <math.h>

using namespace LRender;

float Shape::Leaf::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &color,
	std::vector<Node>::const_iterator a,
	std::vector<Node>::const_iterator aEnd,
	std::vector<Node>::const_iterator b,
	std::vector<Node>::const_iterator bEnd) {
	const auto nBase = ((a + 1)->position - a->position).cross((b + 1)->position - b->position).normalize();
	std::vector<Vertex> verticesA({ Vertex(a->position, nBase, color) });
	std::vector<Vertex> verticesB({ Vertex(b->position, nBase, color) });

	while(++a, ++b, a < aEnd && b < bEnd) {
		auto na = (a->position - (a - 1)->position).cross(b->position - a->position).normalize();
		auto nb = (b->position - (b - 1)->position).cross(b->position - a->position).normalize();

		if(a + 1 != aEnd)
			na = (na + ((a + 1)->position - a->position).cross(b->position - a->position).normalize()) * 0.5f;

		if(b + 1 != bEnd)
			nb = (nb + ((b + 1)->position - b->position).cross(b->position - a->position).normalize()) * 0.5f;

		verticesA.push_back(Vertex(a->position, na, color));
		verticesB.push_back(Vertex(b->position, nb, color));
	}

	if(a != aEnd) {
		--a; --b;

		while(++a < aEnd) {
			auto n = (a->position - (a - 1)->position).cross(b->position - a->position).normalize();

			if(a + 1 != aEnd)
				n = (n + ((a + 1)->position - a->position).cross(b->position - a->position).normalize()) * 0.5f;

			verticesA.push_back(Vertex(
				a->position,
				n,
				color));
		}
	}
	else if(b != bEnd) {
		--a, --b;

		while(++b < bEnd) {
			auto n = (b->position - (b - 1)->position).cross(b->position - a->position).normalize();

			if(b + 1 != bEnd)
				n = (n + ((b + 1)->position - b->position).cross(b->position - a->position).normalize()) * 0.5f;

			verticesB.push_back(Vertex(
				b->position,
				(b->position - (b - 1)->position).cross(b->position - a->position).normalize(),
				color));
		}
	}

	std::vector<Vertex>::const_iterator va = verticesA.begin();
	std::vector<Vertex>::const_iterator vb = verticesB.begin();
	float area = 0;

	while(++va, ++vb, va < verticesA.end() && vb < verticesB.end()) {
		area += pushTriangle(vertices, indices, *va, *vb, *(vb - 1));
		area += pushTriangle(vertices, indices, *(vb - 1), *(va - 1), *va);
	}

	if(va != verticesA.end()) {
		--va;

		while(++va < verticesA.end())
			area += pushTriangle(vertices, indices, *(vb - 1), *(va - 1), *va);
	}
	else if(vb != verticesB.end()) {
		--vb;

		while(++vb < verticesB.end())
			area += pushTriangle(vertices, indices, *(va - 1), *vb, *(vb - 1));
	}		

	return area;
}

float Shape::Leaf::pushTriangle(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	Vertex a,
	Vertex b,
	Vertex c) {
	if(a.position == b.position || a.position == c.position || b.position == c.position)
		return 0;

	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);

	a.normal = -a.normal;
	b.normal = -b.normal;
	c.normal = -c.normal;

	vertices.push_back(c);
	vertices.push_back(b);
	vertices.push_back(a);

	indices.push_back(vertices.size() - 6);
	indices.push_back(vertices.size() - 5);
	indices.push_back(vertices.size() - 4);
	indices.push_back(vertices.size() - 3);
	indices.push_back(vertices.size() - 2);
	indices.push_back(vertices.size() - 1);

	return area(a.position, b.position, c.position);
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