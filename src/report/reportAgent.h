#pragma once

#include "reportLimits.h"
#include "reportArea.h"
#include "reportExposure.h"
#include "math/vector.h"

#include <vector>

namespace LRender {
	class ReportAgent final {
	public:
		ReportAgent(
			std::vector<Vector> seedPositions,
			ReportLimits limits,
			ReportArea area);
		void setExposure(ReportExposure &exposure);
		const std::vector<Vector> &getSeedPositions() const;
		const ReportLimits &getLimits() const;
		const ReportArea &getArea() const;
		const ReportExposure &getExposure() const;

	private:
		const std::vector<Vector> seedPositions;
		const ReportLimits limits;
		const ReportArea area;
		ReportExposure exposure;
	};
}