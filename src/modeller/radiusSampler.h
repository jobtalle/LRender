#pragma once

namespace LRender {
	class RadiusSampler final {
	public:
		RadiusSampler(const float max);
		float sample(const size_t topDist) const;

	private:
		static const float DIST_FALLOFF;

		const float max;
	};
}