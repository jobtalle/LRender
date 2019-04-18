#pragma once

namespace LRender {
	class ReportExposure final {
	public:
		ReportExposure();
		ReportExposure(float exposure);
		ReportExposure &operator=(const ReportExposure &other) = default;
		float getExposure() const;

	private:
		float exposure;
	};
}