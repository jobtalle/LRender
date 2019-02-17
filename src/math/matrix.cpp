#include "matrix.h"

#include <algorithm>
#include <iterator>

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

Matrix &Matrix::operator*(const Matrix &other) {
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

Matrix Matrix::translation(const Vector &translation) {
	return Matrix({
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ translation.x, translation.y, translation.z, 1 }
	});
}

Matrix Matrix::scale(const Vector &scale) {
	return Matrix({
		{ scale.x, 0, 0, 0 },
		{ 0, scale.y, 0, 0 },
		{ 0, 0, scale.z, 0 },
		{ 0, 0, 0, 1 }
	});
}

Matrix Matrix::scale(const float scale) {
	return Matrix::scale(Vector(scale));
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