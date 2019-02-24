#pragma once

#include "math/vector.h"

namespace LRender {
	class Seed final {
	public:
		Seed(const Vector &position);
		const Vector &getPosition() const;

	private:
		const Vector position;
	};
};