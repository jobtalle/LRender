#include "reportAgent.h"

#include <utility>

using namespace LRender;

ReportAgent::ReportAgent(
	std::vector<ReportSeed> seeds,
	const ReportLimits limits,
	const ReportArea area) :
	seeds(std::move(seeds)),
	limits(limits),
	area(area) {

}

void ReportAgent::setExposure(ReportExposure &exposure) {
	this->exposure = exposure;
}

const std::vector<ReportSeed> &ReportAgent::getSeeds() const {
	return seeds;
}

const ReportLimits &ReportAgent::getLimits() const {
	return limits;
}

const ReportArea &ReportAgent::getArea() const {
	return area;
}

const ReportExposure& ReportAgent::getExposure() const {
	return exposure;
}
