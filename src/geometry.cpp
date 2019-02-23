#include "geometry.h"

using namespace LRender;

Geometry::Geometry(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices) :
	vertices(vertices),
	indices(indices) {

}