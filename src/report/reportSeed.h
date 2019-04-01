#pragma once

#include "math/vector.h"

namespace LRender {
	class ReportSeed final {
	public:
		ReportSeed(const Vector &location);
		const Vector &getLocation() const;

	private:
		Vector location;
	};
}