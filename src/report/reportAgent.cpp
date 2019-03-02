#include "reportAgent.h"

using namespace LRender;

ReportAgent::ReportAgent(
	const ReportLimits &limits,
	const ReportArea &area) :
	limits(limits),
	area(area) {

}

const ReportLimits &ReportAgent::getLimits() const {
	return limits;
}

const ReportArea &ReportAgent::getArea() const {
	return area;
}