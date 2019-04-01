#include "reportAgent.h"

#include <utility>

using namespace LRender;

ReportAgent::ReportAgent(
	std::vector<Vector> seedPositions,
	const ReportLimits limits,
	const ReportArea area) :
	seedPositions(std::move(seedPositions)),
	limits(limits),
	area(area) {

}

void ReportAgent::setExposure(ReportExposure &exposure) {
	this->exposure = exposure;
}

const std::vector<Vector> &ReportAgent::getSeedPositions() const {
	return seedPositions;
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
