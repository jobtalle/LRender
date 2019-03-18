#pragma once

#include "reportLimits.h"
#include "reportArea.h"
#include "reportExposure.h"

namespace LRender {
	class ReportAgent final {
	public:
		ReportAgent(
			ReportLimits limits,
			ReportArea area);
		void setExposure(ReportExposure &exposure);
		const ReportLimits &getLimits() const;
		const ReportArea &getArea() const;
		const ReportExposure &getExposure() const;

	private:
		const ReportLimits limits;
		const ReportArea area;
		ReportExposure exposure;
	};
}