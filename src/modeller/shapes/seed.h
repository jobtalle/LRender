#pragma once

#include "vertex.h"
#include "modeller/seed.h"
#include "modeller/radiusSampler.h"

#include <vector>
#include <cstdint>

namespace LRender {
	namespace Shape {
		class Seed final {
		public:
			static void model(
				std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				const Vector &color,
				const RadiusSampler &radiusSampler,
				const LRender::Seed &seed);

		private:
			Seed() = default;

			static const float RADIUS_FACTOR;
			static const float RADIUS_MIN;
		};
	};
};