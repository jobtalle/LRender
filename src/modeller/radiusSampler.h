#pragma once

#include <cstddef>

namespace LRender {
	class RadiusSampler final {
	public:
		RadiusSampler(float max);
		float sampleFactor(size_t topDist) const;
		float sampleRadius(size_t topDist) const;

	private:
		static const float DIST_FALLOFF;

		const float max;
	};
}
