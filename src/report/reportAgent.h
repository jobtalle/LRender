#pragma once

#include "reportLimits.h"
#include "reportArea.h"

namespace LRender {
	class ReportAgent final {
	public:
		ReportAgent(
			const ReportLimits &limits,
			const ReportArea &area);
		const ReportLimits &getLimits() const;
		const ReportArea &getArea() const;

	private:
		const ReportLimits limits;
		const ReportArea area;
	};
}