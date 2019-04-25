#pragma once

#include "math/vector.h"

#include <string>
#include <memory>
#include "../../../LParse/src/growthProfile.h"

namespace LRender {
	class Agent final {
	public:
		Agent(
			const Vector &position,
			std::string symbols,
			size_t ruleCount,
			std::shared_ptr<const LParse::GrowthProfile> growthProfile);
		const Vector &getPosition() const;
		const std::string &getSymbols() const;
		size_t getRuleCount() const;
		const std::shared_ptr<const LParse::GrowthProfile> &getGrowthProfile() const;

	private:
		const Vector position;
		const std::string symbols;
		const size_t ruleCount;
		const std::shared_ptr<const LParse::GrowthProfile> growthProfile;
	};
}
