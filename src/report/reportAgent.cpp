#include "reportAgent.h"

#include <utility>

using namespace LRender;

ReportAgent::ReportAgent(
	std::vector<ReportSeed> seeds,
	ReportLimits limits,
	const ReportArea area,
	const ReportSize size) :
	seeds(std::move(seeds)),
	limits(std::move(limits)),
	area(area),
	size(size) {

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

const ReportSize& ReportAgent::getSize() const {
	return size;
}

const ReportExposure& ReportAgent::getExposure() const {
	return exposure;
}
