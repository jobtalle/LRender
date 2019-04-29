#pragma once

#include "math/vector.h"

namespace LRender {
	struct Vertex {
		Vertex(const Vector &position, const Vector &normal, float cu, float cv);

		Vector position;
		Vector normal;
		float cu, cv;
	};
}