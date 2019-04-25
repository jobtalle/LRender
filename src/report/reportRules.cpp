#include "reportRules.h"

using namespace LRender;

ReportRules::ReportRules(const size_t ruleCount) :
	ruleCount(ruleCount) {
	
}

size_t ReportRules::getRuleCount() const {
	return ruleCount;
}
