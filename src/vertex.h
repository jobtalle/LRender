#pragma once

#include "math/vector.h"

namespace LRender {
	struct Vertex {
		Vertex(const Vector &position, const Vector &normal, const Vector &color);

		Vector position;
		Vector normal;
		Vector color;
	};
}