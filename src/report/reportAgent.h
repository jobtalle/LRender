#pragma once

#include "reportLimits.h"

namespace LRender {
	class ReportAgent final {
	public:
		ReportAgent(const ReportLimits &limits);
		const ReportLimits &getLimits() const;

	private:
		const ReportLimits limits;
	};
}