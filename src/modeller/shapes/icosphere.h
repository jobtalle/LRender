#pragma once

#include "model/vertex.h"
#include "math/quaternion.h"

#include <vector>
#include <cstdint>

namespace LRender {
	namespace Shape {
		class Icosphere final {
		public:
			static void model(
				std::vector<Vertex> &vertices,
				std::vector<uint32_t> &indices,
				const Vector &position,
				const Quaternion &orientation,
				const float radius,
				const size_t subdivisions);

		private:
			Icosphere() = default;

			struct BufferedSphere {
				std::vector<Vector> points;
				std::vector<uint32_t> indices;
			};

			static const BufferedSphere &getSphere(const size_t subdivisions);
			static BufferedSphere subdivide(const BufferedSphere &source);
			static void makeIcosahedron(
				std::vector<Vector> &points,
				std::vector<uint32_t> &indice);

			static std::vector<BufferedSphere> bufferedSpheres;
		};
	};
}