#pragma once

#include <ostream>

namespace LRender {
	class Matrix final {
	public:
		Matrix();
		Matrix &identity();
		float get(const size_t x, const size_t y) const;

	private:
		float m[4][4] = { 0 };
	};
};

std::ostream &operator<<(std::ostream &stream, const LRender::Matrix &matrix);