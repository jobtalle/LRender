#pragma once

#include "math/vector.h"

namespace LRender {
	class Seed final {
	public:
		Seed(const Vector &position);
		void setTopDist(const size_t topDist);
		size_t getTopDist() const;
		const Vector &getPosition() const;

	private:
		const Vector position;
		size_t topDist;
	};
}