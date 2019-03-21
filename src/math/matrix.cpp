#include "matrix.h"

#include <algorithm>
#include <iterator>
#include <cmath>

using namespace LRender;

Matrix::Matrix() {
	identity();
}

Matrix::Matrix(const Matrix &other) {
	*this = other;
}

Matrix::Matrix(const float (&values)[4][4]) {
	std::copy(&values[0][0], &values[0][0] + 16, &m[0][0]);
}

Matrix Matrix::copy() const {
	return Matrix(*this);
}

Matrix &Matrix::identity() {
	for(size_t i = 0; i < 4; ++i)
		m[i][i] = 1;

	return *this;
}

Matrix &Matrix::invert() {
	float s[] = {
		m[0][0] * m[1][1] - m[1][0] * m[0][1],
		m[0][0] * m[1][2] - m[1][0] * m[0][2],
		m[0][0] * m[1][3] - m[1][0] * m[0][3],
		m[0][1] * m[1][2] - m[1][1] * m[0][2],
		m[0][1] * m[1][3] - m[1][1] * m[0][3],
		m[0][2] * m[1][3] - m[1][2] * m[0][3]
	};

	float c[] = {
		m[2][0] * m[3][1] - m[3][0] * m[2][1],
		m[2][0] * m[3][2] - m[3][0] * m[2][2],
		m[2][0] * m[3][3] - m[3][0] * m[2][3],
		m[2][1] * m[3][2] - m[3][1] * m[2][2],
		m[2][1] * m[3][3] - m[3][1] * m[2][3],
		m[2][2] * m[3][3] - m[3][2] * m[2][3]
	};

	float idet = 1.0 / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

	return *this = Matrix({
		{
			(m[1][1] * c[5] - m[1][2] * c[4] + m[1][3] * c[3]) * idet,
			(-m[0][1] * c[5] + m[0][2] * c[4] - m[0][3] * c[3]) * idet,
			(m[3][1] * s[5] - m[3][2] * s[4] + m[3][3] * s[3]) * idet,
			(-m[2][1] * s[5] + m[2][2] * s[4] - m[2][3] * s[3]) * idet
		},
		{
			(-m[1][0] * c[5] + m[1][2] * c[2] - m[1][3] * c[1]) * idet,
			(m[0][0] * c[5] - m[0][2] * c[2] + m[0][3] * c[1]) * idet,
			(-m[3][0] * s[5] + m[3][2] * s[2] - m[3][3] * s[1]) * idet,
			(m[2][0] * s[5] - m[2][2] * s[2] + m[2][3] * s[1]) * idet
		},
		{
			(m[1][0] * c[4] - m[1][1] * c[2] + m[1][3] * c[0]) * idet,
			(-m[0][0] * c[4] + m[0][1] * c[2] - m[0][3] * c[0]) * idet,
			(m[3][0] * s[4] - m[3][1] * s[2] + m[3][3] * s[0]) * idet,
			(-m[2][0] * s[4] + m[2][1] * s[2] - m[2][3] * s[0]) * idet
		},
		{
			(-m[1][0] * c[3] + m[1][1] * c[1] - m[1][2] * c[0]) * idet,
			(m[0][0] * c[3] - m[0][1] * c[1] + m[0][2] * c[0]) * idet,
			(-m[3][0] * s[3] + m[3][1] * s[1] - m[3][2] * s[0]) * idet,
			(m[2][0] * s[3] - m[2][1] * s[1] + m[2][2] * s[0]) * idet
		}
	});
}

Matrix &Matrix::translate(const Vector &translation) {
	return *this *= Matrix::makeTranslate(translation);
}

Matrix &Matrix::scale(const Vector &scale) {
	return *this *= Matrix::makeScale(scale);
}

Matrix &Matrix::rotateX(const float angle) {
	return *this *= Matrix::makeRotateX(angle);
}

Matrix &Matrix::rotateY(const float angle) {
	return *this *= Matrix::makeRotateY(angle);
}

Matrix &Matrix::rotateZ(const float angle) {
	return *this *= Matrix::makeRotateZ(angle);
}

Vector Matrix::operator*(const Vector &other) const {
	return Vector(
		m[0][0] * other.x + m[1][0] * other.y + m[2][0] * other.z + m[3][0],
		m[0][1] * other.x + m[1][1] * other.y + m[2][1] * other.z + m[3][1],
		m[0][2] * other.x + m[1][2] * other.y + m[2][2] * other.z + m[3][2]
	);
}

Matrix &Matrix::operator*=(const Matrix &other) {
	Matrix matrix;

	for(size_t j = 0; j < 4; ++j) for(size_t i = 0; i < 4; ++i) {
		matrix.m[i][j] = m[i][0] * other.m[0][j];

		for(size_t k = 1; k < 4; ++k)
			matrix.m[i][j] += m[i][k] * other.m[k][j];
	}

	return *this = matrix;
}

Matrix &Matrix::operator=(const Matrix &other) {
	std::copy(&other.m[0][0], &other.m[0][0] + 16, &m[0][0]);

	return *this;
}

float Matrix::get(const size_t x, const size_t y) const {
	return m[x][y];
}

Matrix Matrix::makeTranslate(const Vector &translation) {
	return Matrix({
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ translation.x, translation.y, translation.z, 1 }
	});
}

Matrix Matrix::makeScale(const Vector &scale) {
	return Matrix({
		{ scale.x, 0, 0, 0 },
		{ 0, scale.y, 0, 0 },
		{ 0, 0, scale.z, 0 },
		{ 0, 0, 0, 1 }
	});
}

Matrix Matrix::makeRotateX(const float angle) {
	return Matrix({
		{ 1, 0, 0, 0 },
		{ 0, std::cos(angle), -std::sin(angle), 0 },
		{ 0, std::sin(angle), std::cos(angle), 0 },
		{ 0, 0, 0, 1 }
	});
}

Matrix Matrix::makeRotateY(const float angle) {
	return Matrix({
		{ std::cos(angle), 0, std::sin(angle), 0 },
		{ 0, 1, 0, 0 },
		{ -std::sin(angle), 0, std::cos(angle), 0 },
		{ 0, 0, 0, 1 }
	});
}

Matrix Matrix::makeRotateZ(const float angle) {
	return Matrix({
		{ std::cos(angle), -std::sin(angle), 0, 0 },
		{ std::sin(angle), std::cos(angle), 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	});
}

Matrix Matrix::makeLookAt(const Vector &from, const Vector &to, const Vector &up) {
	auto z = (to - from).normalize();
	auto x = z.cross(up).normalize();
	auto y = x.cross(z);

	return Matrix({
		{ x.x, y.x, -z.x, 0 },
		{ x.y, y.y, -z.y, 0 },
		{ x.z, y.z, -z.z, 0 },
		{
			-x.dot(from),
			-y.dot(from),
			z.dot(from),
			1
		}
	});
}

Matrix Matrix::makePerspective(
	const float angle,
	const float aspect,
	const float znear,
	const float zfar) {
	const float a = 1.0 / tan(angle * 0.5);

	return Matrix({
		{ a / aspect, 0, 0, 0 },
		{ 0, a, 0, 0 },
		{ 0, 0, -((zfar + znear) / (zfar - znear)), -1 },
		{ 0, 0, -((2 * zfar * znear) / (zfar - znear)), 0 }
	});
}

Matrix Matrix::makeOrtho(
	const float left,
	const float top,
	const float right,
	const float bottom,
	const float znear,
	const float zfar) {
	return Matrix({
		{ 2.0f / (left - right), 0, 0, 0 },
		{ 0, 2.0f / (top - bottom), 0, 0 },
		{ 0, 0, -2.0f / (zfar- znear), 0 },
		{ -(right + left) / (left - right), -(top + bottom) / (top - bottom), -(zfar + znear) / (zfar - znear), 1 }
	});
}


Matrix LRender::operator*(Matrix lhs, const Matrix &rhs) {
	return lhs *= rhs;
}

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
	for(size_t row = 0; row < 4; ++row) {
		stream << '(';

		for(size_t column = 0; column < 4; ++column) {
			stream << matrix.get(column, row);

			if(column < 3)
				stream << ", ";
		}

		stream << ')';

		if(row < 3)
			stream << std::endl;
	}

	return stream;
}
