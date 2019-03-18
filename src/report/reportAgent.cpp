#include "reportAgent.h"
#include <utility>

using namespace LRender;

ReportAgent::ReportAgent(
	ReportLimits limits,
	ReportArea area) :
	limits(std::move(limits)),
	area(std::move(area)) {

}

void ReportAgent::setExposure(ReportExposure &exposure) {
	this->exposure = exposure;
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
