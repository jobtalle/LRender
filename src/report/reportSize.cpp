#include "reportSize.h"

using namespace LRender;

ReportSize::ReportSize(const size_t nodes) :
	nodes(nodes) {
	
}

size_t ReportSize::getNodes() const {
	return nodes;
}
