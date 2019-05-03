#pragma once

#include "math/vector.h"

namespace LRender {
	class Quaternion final {
	public:
		Quaternion();
		Quaternion(const Vector &xyz, float w);
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Quaternion &other);
		Quaternion &identity();
		Quaternion &operator*=(const Quaternion &other);
		Quaternion &rotate(const Vector &axis, float angle);
		Quaternion &operator=(const Quaternion &other);
		bool operator==(const Quaternion &other) const;

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
}