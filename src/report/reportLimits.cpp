#include "reportLimits.h"

#include <algorithm>

using namespace LRender;

ReportLimits::ReportLimits(const Vector &minimum, const Vector &maximum) :
	minimum(minimum),
	maximum(maximum) {

}

void ReportLimits::add(const ReportLimits &limits) {
	minimum.x = std::min(minimum.x, limits.getMinimum().x);
	minimum.y = std::min(minimum.y, limits.getMinimum().y);
	minimum.z = std::min(minimum.z, limits.getMinimum().z);

	maximum.x = std::max(maximum.x, limits.getMaximum().x);
	maximum.y = std::max(maximum.y, limits.getMaximum().y);
	maximum.z = std::max(maximum.z, limits.getMaximum().z);
}

const Vector &ReportLimits::getMinimum() const {
	return minimum;
}

const Vector &ReportLimits::getMaximum() const {
	return maximum;
}
