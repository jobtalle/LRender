#include "reportSeed.h"

using namespace LRender;

ReportSeed::ReportSeed(const Vector &location) :
	location(location) {
	
}

const Vector& ReportSeed::getLocation() const {
	return location;
}

