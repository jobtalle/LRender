#include "terrainModel.h"

using namespace LRender;

const float TerrainModel::RESOLUTION = 0.1f;

TerrainModel::TerrainModel(const Terrain &terrain) {
	build(terrain);
}

const Model &TerrainModel::getModel() const {
	return *model;
}

void TerrainModel::build(const Terrain &terrain) {
	Geometry geometry;



	model.reset(new Model(geometry));
}