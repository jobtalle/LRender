#pragma once

#include "../vertex.h"
#include "radiusSampler.h"
#include "path.h"

#include <vector>

namespace LRender {
	class Tube final {
	public:
		static void modelTube(
			std::vector<Vertex> &vertices,
			std::vector<uint32_t> &indices,
			const Vector &color,
			const RadiusSampler &radiusSampler,
			const size_t precision,
			const Path &path);
	};
};