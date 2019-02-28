#include "terrain.h"

using namespace LRender;

Terrain::Terrain(
	const float width,
	const float height,
	const std::function<float(const float x, const float y)> get) :
	width(width),
	height(height),
	get(get) {

}

float Terrain::getWidth() const {
	return width;
}

float Terrain::getHeight() const {
	return height;
}