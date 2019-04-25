#pragma once

namespace LRender {
	class ReportRules final {
	public:
		ReportRules(size_t ruleCount);
		size_t getRuleCount() const;

	private:
		const size_t ruleCount;
	};
}