#pragma once

#include "reportAgent.h"
#include "report/reportLimits.h"

#include <vector>
#include <memory>

namespace LRender {
	class Report final {
	public:
		Report();
		void add(const ReportAgent &agent);
		const std::vector<ReportAgent> &getAgents() const;
		const ReportLimits &getLimits() const;

	private:
		std::vector<ReportAgent> agents;
		std::shared_ptr<ReportLimits> limits;
	};
};
