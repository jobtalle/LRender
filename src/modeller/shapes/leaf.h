#pragma once

#include "../../vertex.h"
#include "../node.h"

#include <vector>

namespace LRender {
	namespace Shape {
		class Leaf final {
		public:
			static float model(
				std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				const Vector &color,
				std::vector<Node>::const_iterator a,
				std::vector<Node>::const_iterator aEnd,
				std::vector<Node>::const_iterator b,
				std::vector<Node>::const_iterator bEnd);

		private:
			Leaf() = default;
			
			static float pushTriangle(
				std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				const Vector &a,
				const Vector &b,
				const Vector &c,
				const Vector &color);
			static float area(
				const Vector &a,
				const Vector &b,
				const Vector &c);
		};
	};
};