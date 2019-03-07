#pragma once

#include "model/vertex.h"
#include "modeller/radiusSampler.h"
#include "modeller/branch.h"

#include <vector>

namespace LRender {
	namespace Shape {
		class Branch final {
		public:
			static void model(
				std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				const Vector &color,
				const RadiusSampler &radiusSampler,
				const size_t precision,
				const LRender::Branch &branch);

		private:
			Branch() = default;

			static std::vector<Vector> makeRing(const size_t precision);
		};
	};
}