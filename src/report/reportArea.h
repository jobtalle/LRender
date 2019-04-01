#pragma once

namespace LRender {
	class ReportArea final {
	public:
		ReportArea(float area);
		float getArea() const;

	private:
		const float area;
	};
}