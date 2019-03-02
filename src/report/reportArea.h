#pragma once

namespace LRender {
	class ReportArea final {
	public:
		ReportArea(const float area);
		float getArea() const;

	private:
		const float area;
	};
}