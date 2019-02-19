#include "modeller.h"

using namespace LRender;

void Modeller::makeTube(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	const std::vector<Vector> path) {
	for(auto point : path) {
		vertices.push_back(Vertex(
			point,
			Vector(0.3, 0.4, 0.5)
		));

		vertices.push_back(Vertex(
			point + Vector(0.1, 0, 0),
			Vector(0.3, 0.4, 0.5)
		));

		if(point != *path.begin()) {
			const size_t size = vertices.size();

			indices.push_back(size - 1);
			indices.push_back(size - 2);
			indices.push_back(size - 4);
			indices.push_back(size - 4);
			indices.push_back(size - 3);
			indices.push_back(size - 1);

			indices.push_back(size - 1);
			indices.push_back(size - 4);
			indices.push_back(size - 2);
			indices.push_back(size - 4);
			indices.push_back(size - 1);
			indices.push_back(size - 3);
		}
	}
}