#include "terrain.h"
#include <utility>

using namespace LRender;

Terrain::Terrain(
	const float width,
	const float height,
	std::shared_ptr<const void> terrainSource,
	std::function<float(float x, float y)> get) :
	terrainSource(std::move(terrainSource)),
	get(std::move(get)),
	width(width),
	height(height) {

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