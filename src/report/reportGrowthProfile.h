#pragma once

#include "lparse.h"

#include <memory>

namespace LRender {
	class ReportGrowthProfile final {
	public:
		ReportGrowthProfile(std::shared_ptr<const LParse::GrowthProfile> profile);
		const LParse::GrowthProfile &getProfile() const;

	private:
		const std::shared_ptr<const LParse::GrowthProfile> profile;
	};
}