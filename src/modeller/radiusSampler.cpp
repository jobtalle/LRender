#include "radiusSampler.h"

using namespace LRender;

const float RadiusSampler::DIST_FALLOFF = 150;

RadiusSampler::RadiusSampler(const float max) :
	max(max) {

}

float RadiusSampler::sample(const size_t topDist) const {
	return (1 - (1 / (float(topDist) / DIST_FALLOFF + 1))) * 0.1f;
}