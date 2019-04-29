#include "icosphere.h"

using namespace LRender;

std::vector<Shape::Icosphere::BufferedSphere> Shape::Icosphere::bufferedSpheres;

void Shape::Icosphere::model(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const Vector &position,
	const Quaternion &orientation,
	const float radius,
	const size_t subdivisions) {
	const BufferedSphere &sphere = getSphere(subdivisions);
	const size_t firstIndex = vertices.size();

	for(auto &point : sphere.points)
		vertices.emplace_back(position + orientation * point * radius, point, 1.0f, 1.0f);

	for(auto index : sphere.indices)
		indices.push_back(firstIndex + index);
}

const Shape::Icosphere::BufferedSphere &Shape::Icosphere::getSphere(const size_t subdivisions) {
	while(subdivisions >= bufferedSpheres.size()) {
		if(bufferedSpheres.empty()) {
			BufferedSphere newSphere;

			makeIcosahedron(newSphere.points, newSphere.indices);

			bufferedSpheres.push_back(newSphere);
		}
		else
			bufferedSpheres.push_back(subdivide(*--bufferedSpheres.end()));
	}

	return bufferedSpheres[subdivisions];
}

Shape::Icosphere::BufferedSphere Shape::Icosphere::subdivide(const Shape::Icosphere::BufferedSphere &source) {
	BufferedSphere sphere;

	sphere.points.insert(sphere.points.begin(), source.points.begin(), source.points.end());

	for(auto triangle = source.indices.begin(); triangle < source.indices.end(); std::advance(triangle, 3)) {
		const uint32_t ia = *triangle;
		const uint32_t ib = *(triangle + 1);
		const uint32_t ic = *(triangle + 2);
		const uint32_t iab = sphere.points.size();
		const uint32_t ibc = sphere.points.size() + 1;
		const uint32_t ica = sphere.points.size() + 2;

		sphere.points.push_back((*(source.points.begin() + ia) + *(source.points.begin() + ib)).normalize());
		sphere.points.push_back((*(source.points.begin() + ib) + *(source.points.begin() + ic)).normalize());
		sphere.points.push_back((*(source.points.begin() + ic) + *(source.points.begin() + ia)).normalize());

		sphere.indices.insert(sphere.indices.end(), { ia, iab, ica });
		sphere.indices.insert(sphere.indices.end(), { ib, ibc, iab });
		sphere.indices.insert(sphere.indices.end(), { ic, ica, ibc });
		sphere.indices.insert(sphere.indices.end(), { iab, ibc, ica });
	}

	return sphere;
}

void Shape::Icosphere::makeIcosahedron(
	std::vector<Vector> &points,
	std::vector<uint32_t> &indices) {
	float w = (1 + sqrt(5)) * 0.5f;
	const float h = 1.0f / sqrt(1 + w * w);

	w *= h;

	points.emplace_back(Vector(-h, w, 0));
	points.emplace_back(Vector(h, w, 0));
	points.emplace_back(Vector(-h, -w, 0));
	points.emplace_back(Vector(h, -w, 0));

	points.emplace_back(Vector(0, -h, w));
	points.emplace_back(Vector(0, h, w));
	points.emplace_back(Vector(0, -h, -w));
	points.emplace_back(Vector(0, h, -w));

	points.emplace_back(Vector(w, 0, -h));
	points.emplace_back(Vector(w, 0, h));
	points.emplace_back(Vector(-w, 0, -h));
	points.emplace_back(Vector(-w, 0, h));

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