#include "vector.h"

#include <math.h>

using namespace LRender;

Vector::Vector() :
	x(0),
	y(0),
	z(0) {

}

Vector::Vector(const float n) :
	x(n),
	y(n),
	z(n) {

}

Vector::Vector(const float x, const float y, const float z) :
	x(x),
	y(y),
	z(z) {

}

Vector::Vector(const Vector &other) {
	*this = other;
}

float Vector::length() const {
	return sqrt(x * x + y * y + z * z);
}

float Vector::dot(const Vector &other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vector Vector::copy() const {
	return Vector(x, y, z);
}

Vector Vector::cross(const Vector &other) const {
	return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector &Vector::normalize() {
	const float f = 1.0 / length();

	return *this * f;
}

Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}

Vector &Vector::operator*(const float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector &Vector::operator*(const Vector &other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector &Vector::operator+(const Vector &other) {
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector &Vector::operator-(const Vector &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector &Vector::operator=(const Vector &other) {
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

bool Vector::operator==(const Vector &other) const {
	return x == other.x && y == other.y && z == other.z;
}

bool Vector::operator!=(const Vector &other) const {
	return !(*this == other);
}

std::ostream &operator<<(std::ostream &stream, const Vector &vector) {
	stream << '(' << vector.x << ", " << vector.y << ", " << vector.z << ')';

	return stream;
}