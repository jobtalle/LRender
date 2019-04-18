#include "reportAgent.h"

#include <utility>

using namespace LRender;

ReportAgent::ReportAgent(
	std::vector<ReportSeed> seeds,
	std::vector<ReportLeaf> leaves,
	ReportLimits limits,
	const ReportSize size) :
	seeds(std::move(seeds)),
	leaves(std::move(leaves)),
	limits(std::move(limits)),
	size(size) {

}

void ReportAgent::setExposure(ReportExposure &exposure) {
	this->exposure = exposure;
}

const std::vector<ReportSeed> &ReportAgent::getSeeds() const {
	return seeds;
}

const std::vector<ReportLeaf> &ReportAgent::getLeaves() const {
	return leaves;
}

const ReportLimits &ReportAgent::getLimits() const {
	return limits;
}

const ReportSize& ReportAgent::getSize() const {
	return size;
}

const ReportExposure& ReportAgent::getExposure() const {
	return exposure;
}
