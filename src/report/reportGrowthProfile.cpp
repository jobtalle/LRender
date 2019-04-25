#include "reportGrowthProfile.h"

#include <utility>

using namespace LRender;

ReportGrowthProfile::ReportGrowthProfile(std::shared_ptr<const LParse::GrowthProfile> profile) :
	profile(std::move(profile)) {
	
}

const LParse::GrowthProfile &ReportGrowthProfile::getProfile() const {
	return *profile;
}
