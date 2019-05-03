#pragma once

#include "model/vertex.h"
#include "modeller/node.h"

#include <vector>
#include <cstdint>

namespace LRender {
	namespace Shape {
		class Leaf final {
		public:
			static float model(
				std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				float fertility,
				std::vector<Node>::const_iterator a,
				const std::vector<Node>::const_iterator &aEnd,
				std::vector<Node>::const_iterator b,
				const std::vector<Node>::const_iterator &bEnd);

		private:
			Leaf() = default;
			
			static float addTriangle(
				const std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				uint32_t a,
				uint32_t b,
				uint32_t c);
		};
	};
}
