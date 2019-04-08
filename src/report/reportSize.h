#pragma once

namespace LRender {
	class ReportSize final {
	public:
		ReportSize(size_t nodes);
		size_t getNodes() const;

	private:
		const size_t nodes;
	};
}