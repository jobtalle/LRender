#include "reportLimits.h"

using namespace LRender;

ReportLimits::ReportLimits(const Vector &minimum, const Vector &maximum) :
	minimum(minimum),
	maximum(maximum) {

}

const Vector &ReportLimits::getMinimum() const {
	return minimum;
}

const Vector &ReportLimits::getMaximum() const {
	return maximum;
}