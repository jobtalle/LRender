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
		Matrix &invert();
		Matrix &translate(const Vector &translation);
		Matrix &scale(const Vector &scale);
		Matrix &rotateX(const float angle);
		Matrix &rotateY(const float angle);
		Matrix &rotateZ(const float angle);
		Vector operator*(const Vector &other) const;
		Matrix &operator*=(const Matrix &other);
		Matrix &operator=(const Matrix &other);
		float get(const size_t x, const size_t y) const;

		static Matrix makeTranslate(const Vector &translation);
		static Matrix makeScale(const Vector &scale);
		static Matrix makeRotateX(const float angle);
		static Matrix makeRotateY(const float angle);
		static Matrix makeRotateZ(const float angle);
		static Matrix makeLookAt(const Vector &from, const Vector &to, const Vector &up);
		static Matrix makePerspective(
			const float angle,
			const float aspect,
			const float znear,
			const float zfar);
		static Matrix makeOrtho(
			const float left,
			const float top,
			const float right,
			const float bottom,
			const float znear,
			const float zfar);

	private:
		float m[4][4] = { { 0 } };

		Matrix(const float (&values)[4][4]);
	};

	Matrix operator*(Matrix lhs, const Matrix &rhs);
}

std::ostream &operator<<(std::ostream &stream, const LRender::Matrix &matrix);