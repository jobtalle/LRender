#pragma once

#include "report/reportAgent.h"
#include "report/reportLimits.h"

#include <vector>
#include <memory>

namespace LRender {
	class Report final {
	public:
		Report() = default;
		void add(const ReportAgent &agent);
		std::vector<ReportAgent> &getAgents();
		const ReportLimits &getLimits() const;
		bool hasLimits() const;

	private:
		std::vector<ReportAgent> agents;
		std::shared_ptr<ReportLimits> limits;
	};
}