#pragma once

#include "model/vertex.h"
#include "math/quaternion.h"

#include <vector>
#include <cstdint>

namespace LRender {
	namespace Shape {
		class StandardLeaf final {
		public:
			static float modelA(
				std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				float fertility,
				const Vector &position,
				const Quaternion &orientation);

		private:
			static const Vector NORMAL;
			static std::vector<Vector> makeShape();
		};
	}
}
