#include "terrain.h"

using namespace LRender;

Terrain::Terrain(
	const float width,
	const float height,
	const std::shared_ptr<const void> terrainSource,
	const std::function<float(const float x, const float y)> get) :
	width(width),
	height(height),
	terrainSource(terrainSource),
	get(get) {

}

float Terrain::getWidth() const {
	return width;
}

float Terrain::getHeight() const {
	return height;
}

float Terrain::getY(const float x, const float y) const {
	return get(x, y);
}