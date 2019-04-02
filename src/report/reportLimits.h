#pragma once

#include "math/vector.h"

namespace LRender {
	class ReportLimits final {
	public:
		ReportLimits(const Vector &minimum, const Vector &maximum);
		void add(const ReportLimits &limits);
		const Vector &getMinimum() const;
		const Vector &getMaximum() const;
		float getRadius() const;

	private:
		Vector minimum;
		Vector maximum;
	};
}