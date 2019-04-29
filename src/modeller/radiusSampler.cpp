#include "radiusSampler.h"

using namespace LRender;

const float RadiusSampler::DIST_FALLOFF = 150;

RadiusSampler::RadiusSampler(const float max) :
	max(max) {

}

float RadiusSampler::sampleFactor(const size_t topDist) const {
	return (1 - (1 / (float(topDist) / DIST_FALLOFF + 1)));
}

float RadiusSampler::sampleRadius(const size_t topDist) const {
	return sampleFactor(topDist) * max;
}