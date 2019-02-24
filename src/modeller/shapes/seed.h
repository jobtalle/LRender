#pragma once

#include "vertex.h"
#include "modeller/seed.h"

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
				const LRender::Seed &seed);

		private:
			Seed() = default;
		};
	};
};