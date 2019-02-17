#include "matrix.h"

using namespace LRender;

Matrix::Matrix() {
	identity();
}

Matrix &Matrix::identity() {
	for(size_t i = 0; i < 4; ++i)
		m[i][i] = 1;

	return *this;
}

float Matrix::get(const size_t x, const size_t y) const {
	return m[x][y];
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