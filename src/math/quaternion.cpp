#include "quaternion.h"

#include <math.h>

using namespace LRender;

Quaternion::Quaternion() {
	identity();
}

Quaternion::Quaternion(const Vector &xyz, const float w) :
	xyz(xyz),
	w(w) {

}

Quaternion::Quaternion(const float x, const float y, const float z, const float w) :
	x(x),
	y(y),
	z(z),
	w(w) {

}

Quaternion::Quaternion(const Quaternion &other) {
	*this = other;
}

Quaternion &Quaternion::identity() {
	x = y = z = 0;
	w = 1;

	return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &other) {
	return *this = *this * other;
}

Quaternion &Quaternion::rotate(const Vector &axis, const float angle) {
	return *this *= makeRotation(axis, angle);
}

Quaternion &Quaternion::operator=(const Quaternion &other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

Quaternion Quaternion::makeRotation(const Vector &axis, const float angle) {
	return Quaternion(
		axis * sin(angle * 0.5),
		cos(angle * 0.5)
	);
}

bool Quaternion::operator==(const Quaternion &other) const {
	return xyz == other.xyz && w == other.w;
}

Quaternion LRender::operator*(Quaternion lhs, const Quaternion &rhs) {
	return Quaternion(
		lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
	);
}

Vector LRender::operator*(const Quaternion &lhs, const Vector &rhs) {
	Vector t(lhs.xyz.cross(rhs) * 2);

	return rhs + t * lhs.w + lhs.xyz.cross(t);
}