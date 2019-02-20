#pragma once

#include "../math/vector.h"
#include "../math/quaternion.h"

namespace LRender {
	struct Node {
		Node(const Vector &position, const Quaternion &heading, const float radius);
		Node &extrude(const float distance);

		Vector position;
		Quaternion heading;
		float radius;
	};
}