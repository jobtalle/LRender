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
				const RadiusSampler &radiusSampler,
				float fertility,
				size_t precision,
				const LRender::Branch &branch);

		private:
			Branch() = default;

			static std::vector<Vector> makeRing(size_t precision);
		};
	};
}