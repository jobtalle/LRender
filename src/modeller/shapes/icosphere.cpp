#include "icosphere.h"

#include <math.h>

using namespace LRender;

std::vector<Shape::Icosphere::BufferedSphere> Shape::Icosphere::bufferedSpheres;

void Shape::Icosphere::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &color,
	const Vector &position,
	const Quaternion &orientation,
	const float radius,
	const size_t subdivisions) {
	const BufferedSphere &sphere = getIcosahedron(subdivisions);
	const size_t firstIndex = vertices.size();

	for(auto &point : sphere.points)
		vertices.push_back(Vertex(position + orientation * point * radius, point, color));

	for(auto index : sphere.indices)
		indices.push_back(firstIndex + index);
}

const Shape::Icosphere::BufferedSphere &Shape::Icosphere::getIcosahedron(const size_t subdivisions) {
	while(subdivisions >= bufferedSpheres.size()) {
		BufferedSphere newSphere;

		if(bufferedSpheres.size() == 0)
			makeIcosahedron(newSphere.points, newSphere.indices);
		// TODO: else, subdivide

		bufferedSpheres.push_back(newSphere);
	}

	return bufferedSpheres[subdivisions];
}

void Shape::Icosphere::makeIcosahedron(
	std::vector<Vector> &points,
	std::vector<uint32_t> &indices) {
	float w = (1 + sqrt(5)) * 0.5f;
	const float h = 1.0f / sqrt(1 + w * w);

	w *= h;

	points.push_back(Vector(-h, w, 0));
	points.push_back(Vector(h, w, 0));
	points.push_back(Vector(-h, -w, 0));
	points.push_back(Vector(h, -w, 0));

	points.push_back(Vector(0, -h, w));
	points.push_back(Vector(0, h, w));
	points.push_back(Vector(0, -h, -w));
	points.push_back(Vector(0, h, -w));

	points.push_back(Vector(w, 0, -h));
	points.push_back(Vector(w, 0, h));
	points.push_back(Vector(-w, 0, -h));
	points.push_back(Vector(-w, 0, h));

	indices.insert(indices.end(), { 0, 11, 5 });
	indices.insert(indices.end(), { 0, 5, 1 });
	indices.insert(indices.end(), { 0, 1, 7 });
	indices.insert(indices.end(), { 0, 7, 10 });
	indices.insert(indices.end(), { 0, 10, 11 });

	indices.insert(indices.end(), { 1, 5, 9 });
	indices.insert(indices.end(), { 5, 11, 4 });
	indices.insert(indices.end(), { 11, 10, 2 });
	indices.insert(indices.end(), { 10, 7, 6 });
	indices.insert(indices.end(), { 7, 1, 8 });

	indices.insert(indices.end(), { 3, 9, 4 });
	indices.insert(indices.end(), { 3, 4, 2 });
	indices.insert(indices.end(), { 3, 2, 6 });
	indices.insert(indices.end(), { 3, 6, 8 });
	indices.insert(indices.end(), { 3, 8, 9 });

	indices.insert(indices.end(), { 4, 9, 5 });
	indices.insert(indices.end(), { 2, 4, 11 });
	indices.insert(indices.end(), { 6, 2, 10 });
	indices.insert(indices.end(), { 8, 6, 7 });
	indices.insert(indices.end(), { 9, 8, 1 });
}