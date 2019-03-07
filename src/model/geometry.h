#pragma once

#include "vertex.h"

#include <cstdint>
#include <vector>

namespace LRender {
	struct Geometry {
	public:
		Geometry() = default;
		Geometry(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}