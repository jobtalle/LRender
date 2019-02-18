#pragma once

#include "math/vector.h"

namespace LRender {
	struct Vertex {
		Vertex(const Vector &position, const Vector &color);

		Vector position;
		Vector color;
	};
}