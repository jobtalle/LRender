#include "reportAgent.h"

#include <utility>

using namespace LRender;

ReportAgent::ReportAgent(
	const Vector &position,
	const Vector &average,
	std::vector<ReportSeed> seeds,
	std::vector<ReportLeaf> leaves,
	ReportLimits limits,
	const ReportSize size,
	const ReportRules rules,
	ReportGrowthProfile growthProfile) :
	position(position),
	average(average),
	seeds(std::move(seeds)),
	leaves(std::move(leaves)),
	limits(std::move(limits)),
	size(size),
	rules(rules),
	growthProfile(std::move(growthProfile)) {

}

const Vector &ReportAgent::getPosition() const {
	return position;
}

const Vector &ReportAgent::getAverage() const {
	return average;
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

const ReportSize &ReportAgent::getSize() const {
	return size;
}

const ReportExposure &ReportAgent::getExposure() const {
	return exposure;
}

const ReportRules &ReportAgent::getRules() const {
	return rules;
}

const ReportGrowthProfile &ReportAgent::getGrowthProfile() const {
	return growthProfile;
}
