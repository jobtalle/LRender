#include "report.h"

using namespace LRender;

Report::Report() {

}

void Report::add(const ReportAgent &agent) {
	agents.push_back(agent);
}

const std::vector<ReportAgent> &Report::getAgents() const {
	return agents;
}