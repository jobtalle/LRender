#include "reportArea.h"

using namespace LRender;

ReportArea::ReportArea(const float area) :
	area(area) {

}

float ReportArea::getArea() const {
	return area;
}