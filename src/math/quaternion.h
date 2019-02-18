#pragma once

#include "vector.h"

namespace LRender {
	class Quaternion final {
	public:
		Quaternion();
		Quaternion(const Vector &xyz, const float w);
		Quaternion(const float x, const float y, const float z, const float w);
		Quaternion(const Quaternion &other);
		Quaternion &identity();
		Quaternion &operator*=(const Quaternion &other);
		Quaternion &rotate(const Vector &axis, const float angle);
		Quaternion &operator=(const Quaternion &other);

		static Quaternion makeRotation(const Vector &axis, const float angle);

		union {
			struct {
				float x, y, z;
			};

			Vector xyz;
		};

		float w;
	};

	Quaternion operator*(Quaternion lhs, const Quaternion &rhs);
	Vector operator*(const Quaternion &lhs, const Vector &rhs);
};