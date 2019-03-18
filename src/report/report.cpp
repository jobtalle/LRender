#include "report.h"

using namespace LRender;

void Report::add(const ReportAgent &agent) {
	agents.push_back(agent);

	if(!limits)
		limits = std::make_unique<ReportLimits>(agent.getLimits());
	else
		limits->add(agent.getLimits());
}

std::vector<ReportAgent> &Report::getAgents() {
	return agents;
}

const ReportLimits &Report::getLimits() const {
	return *limits;
}

bool Report::hasLimits() const {
	return !agents.empty();
}
