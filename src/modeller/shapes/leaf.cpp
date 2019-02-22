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
	float area = 0;
	std::vector<Node>::const_iterator aPrevious(a++);
	std::vector<Node>::const_iterator bPrevious(b++);

	while(a < aEnd && b < bEnd) {
		area += pushTriangle(
			vertices,
			indices,
			a->position,
			b->position,
			bPrevious->position,
			color);
		area += pushTriangle(
			vertices,
			indices,
			bPrevious->position,
			aPrevious->position,
			a->position,
			color);

		aPrevious = a++;
		bPrevious = b++;
	}

	for(; a < aEnd; ++a)
		area += pushTriangle(
			vertices,
			indices,
			a->position,
			aPrevious->position,
			bPrevious->position,
			color);

	for(; b < bEnd; ++b)
		area += pushTriangle(
			vertices,
			indices,
			b->position,
			bPrevious->position,
			aPrevious->position,
			color);

	return area;
}

float Shape::Leaf::pushTriangle(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &a,
	const Vector &b,
	const Vector &c,
	const Vector &color) {
	if(a == b || a == c || b == c)
		return 0;

	Vector normal = (a - b).cross(b - c).normalize();

	vertices.push_back(Vertex(a, normal, color));
	vertices.push_back(Vertex(b, normal, color));
	vertices.push_back(Vertex(c, normal, color));
	vertices.push_back(Vertex(c, -normal, color));
	vertices.push_back(Vertex(b, -normal, color));
	vertices.push_back(Vertex(a, -normal, color));

	indices.push_back(vertices.size() - 6);
	indices.push_back(vertices.size() - 5);
	indices.push_back(vertices.size() - 4);
	indices.push_back(vertices.size() - 3);
	indices.push_back(vertices.size() - 2);
	indices.push_back(vertices.size() - 1);

	return area(a, b, c);
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