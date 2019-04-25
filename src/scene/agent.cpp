#include "agent.h"

#include <utility>

using namespace LRender;

Agent::Agent(
	const Vector &position,
	std::string symbols,
	const size_t ruleCount,
	std::shared_ptr<const LParse::GrowthProfile> growthProfile) :
	position(position),
	symbols(std::move(symbols)),
	ruleCount(ruleCount),
	growthProfile(std::move(growthProfile)) {

}

const Vector &Agent::getPosition() const {
	return position;
}

const std::string &Agent::getSymbols() const {
	return symbols;
}

size_t Agent::getRuleCount() const {
	return ruleCount;
}

const std::shared_ptr<const LParse::GrowthProfile> &Agent::getGrowthProfile() const {
	return growthProfile;
}
