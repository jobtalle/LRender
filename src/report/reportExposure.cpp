#include "reportExposure.h"

using namespace LRender;

ReportExposure::ReportExposure() :
	exposure(0) {
	
}

ReportExposure::ReportExposure(const float exposure) :
	exposure(exposure) {
	
}

float ReportExposure::getExposure() const {
	return exposure;
}
