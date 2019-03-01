#pragma once

#include "reportAgent.h"

#include <vector>

namespace LRender {
	class Report final {
	public:
		Report();
		void add(const ReportAgent &agent);
		const std::vector<ReportAgent> &getAgents() const;

	private:
		std::vector<ReportAgent> agents;
	};
};