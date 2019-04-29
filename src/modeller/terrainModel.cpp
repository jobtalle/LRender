#include "terrainModel.h"

#include <vector>

using namespace LRender;

const float TerrainModel::RESOLUTION = 0.25f;

TerrainModel::TerrainModel(const Terrain &terrain) {
	build(terrain);
}

const Model &TerrainModel::getModel() const {
	return *model;
}

void TerrainModel::build(const Terrain &terrain) {
	Geometry geometry;
	const Vector up(0, 1, 0);
	const uint32_t xCells = ceil(terrain.getWidth() / RESOLUTION);
	const uint32_t yCells = ceil(terrain.getHeight() / RESOLUTION);
	const auto dy = terrain.getHeight() / yCells;
	const auto dx = terrain.getWidth() / xCells;
	std::vector<Vector> points;
	
	points.reserve(xCells * yCells + 4);
	geometry.vertices.reserve(xCells * yCells);
	geometry.indices.reserve((xCells - 1) * (yCells - 1) * 6);

	for(size_t y = 0; y <= yCells; ++y) for(size_t x = 0; x <= xCells; ++x)
		points.emplace_back(x * dx, terrain.getY(x * dx, y * dy), y * dy);

	for(size_t y = 0; y <= yCells; ++y) for(size_t x = 0; x <= xCells; ++x) {
		const uint32_t index = x + y * (xCells + 1);
		const auto &point = points[index];
		Vector normal;

		if(x != 0 && y != 0)
			normal += (point - points[index - xCells - 1]).cross(point - points[index - 1]);

		if(x != 0 && y != yCells)
			normal += (point - points[index - 1]).cross(point - points[index + xCells + 1]);

		if(y != yCells && x != xCells)
			normal += (point - points[index + xCells + 1]).cross(point - points[index + 1]);

		if(x != xCells && y != 0)
			normal += (point - points[index + 1]).cross(point - points[index - xCells - 1]);

		geometry.vertices.emplace_back(
			points[index],
			normal.normalize(),
			points[index].y, 0.0f);

		if(x != xCells && y != yCells) {
			if((x & 1) && (y & 1)) {
				geometry.indices.insert(geometry.indices.end(),
				{ index + xCells + 1, index + xCells + 2, index + 1 });
				geometry.indices.insert(geometry.indices.end(),
				{ index + 1, index, index + xCells + 1 });
			}
			else {
				geometry.indices.insert(geometry.indices.end(),
				{ index + xCells + 2, index + 1, index });
				geometry.indices.insert(geometry.indices.end(),
				{ index, index + xCells + 1, index + xCells + 2 });
			}
		}
	}

	model = std::make_unique<Model>(geometry);
}
