#pragma once

#include "math/vector.h"

namespace LRender {
	class ReportLimits final {
	public:
		ReportLimits(const Vector &minimum, const Vector &maximum);
		const Vector &getMinimum() const;
		const Vector &getMaximum() const;

	private:
		const Vector minimum;
		const Vector maximum;
	};
};