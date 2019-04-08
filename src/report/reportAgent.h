#pragma once

#include "reportLimits.h"
#include "reportArea.h"
#include "reportExposure.h"
#include "reportSeed.h"
#include "reportSize.h"

#include <vector>

namespace LRender {
	class ReportAgent final {
	public:
		ReportAgent(
			std::vector<ReportSeed> seeds,
			ReportLimits limits,
			ReportArea area,
			ReportSize size);
		void setExposure(ReportExposure &exposure);
		const std::vector<ReportSeed> &getSeeds() const;
		const ReportLimits &getLimits() const;
		const ReportArea &getArea() const;
		const ReportSize &getSize() const;
		const ReportExposure &getExposure() const;

	private:
		const std::vector<ReportSeed> seeds;
		const ReportLimits limits;
		const ReportArea area;
		const ReportSize size;
		ReportExposure exposure;
	};
}