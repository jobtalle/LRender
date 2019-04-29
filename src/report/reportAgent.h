#pragma once

#include "reportLimits.h"
#include "reportExposure.h"
#include "reportSeed.h"
#include "reportSize.h"
#include "reportLeaf.h"
#include "math/vector.h"

#include <vector>
#include "reportRules.h"
#include "reportGrowthProfile.h"

namespace LRender {
	class ReportAgent final {
	public:
		ReportAgent(
			const Vector &position,
			const Vector &average,
			std::vector<ReportSeed> seeds,
			std::vector<ReportLeaf> leaves,
			ReportLimits limits,
			ReportSize size,
			ReportRules rules,
			ReportGrowthProfile growthProfile);
		void setExposure(ReportExposure &exposure);
		const Vector &getPosition() const;
		const Vector &getAverage() const;
		const std::vector<ReportSeed> &getSeeds() const;
		const std::vector<ReportLeaf> &getLeaves() const;
		const ReportLimits &getLimits() const;
		const ReportSize &getSize() const;
		const ReportExposure &getExposure() const;
		const ReportRules &getRules() const;
		const ReportGrowthProfile &getGrowthProfile() const;

	private:
		const Vector position;
		const Vector average;
		const std::vector<ReportSeed> seeds;
		const std::vector<ReportLeaf> leaves;
		const ReportLimits limits;
		const ReportSize size;
		const ReportRules rules;
		const ReportGrowthProfile growthProfile;
		ReportExposure exposure;
	};
}
