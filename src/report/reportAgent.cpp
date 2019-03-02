#include "reportAgent.h"

using namespace LRender;

ReportAgent::ReportAgent(const ReportLimits &limits) :
	limits(limits) {

}

const ReportLimits &ReportAgent::getLimits() const {
	return limits;
}