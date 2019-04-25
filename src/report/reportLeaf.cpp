#include "reportLeaf.h"

using namespace LRender;

ReportLeaf::ReportLeaf(const float area) :
	area(area) {
	
}

float ReportLeaf::getArea() const {
	return area;
}
