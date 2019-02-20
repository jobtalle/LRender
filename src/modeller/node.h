#pragma once

#include "../math/vector.h"
#include "../math/quaternion.h"

namespace LRender {
	struct Node {
		Node(const Vector &position, const Quaternion &heading);
		Node &extrude(const float distance);
		bool operator==(const Node &other) const;

		Vector position;
		Quaternion heading;
		size_t topDist;
	};
}