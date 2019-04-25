#pragma once

namespace LRender {
	class ReportLeaf final {
	public:
		ReportLeaf(float area);
		float getArea() const;

	private:
		const float area;
	};
}