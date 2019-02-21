#pragma once

#include "../math/vector.h"
#include "../math/quaternion.h"

namespace LRender {
	class Node final {
	public:
		Node(const Vector &position, const float angle);
		Node &extrude(const float distance);
		Node &roll(const float radians);
		Node &pitch(const float radians);
		Quaternion getHeading() const;
		bool operator==(const Node &other) const;

		Vector position;
		Quaternion rollCompensation;
		size_t topDist;

	private:
		static const Vector UP;
		static const Vector AXIS_PITCH;
		static const Vector AXIS_ROLL;

		Quaternion heading;
	};
}