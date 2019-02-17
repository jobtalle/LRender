#pragma once

#include "vector.h"

#include <ostream>

namespace LRender {
	class Matrix final {
	public:
		Matrix();
		Matrix(const Matrix &other);
		Matrix copy() const;
		Matrix &identity();
		Matrix &operator*(const Matrix &other);
		Matrix &operator=(const Matrix &other);
		float get(const size_t x, const size_t y) const;

		static Matrix translation(const Vector &translation);
		static Matrix scale(const Vector &scale);
		static Matrix scale(const float scale);

	private:
		float m[4][4] = { 0 };

		Matrix(const float (&values)[4][4]);
	};
};

std::ostream &operator<<(std::ostream &stream, const LRender::Matrix &matrix);