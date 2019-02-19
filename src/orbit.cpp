#include "orbit.h"

using namespace LRender;

const Vector Orbit::UP = Vector(0, 1, 0);
const float Orbit::RADIANS_PER_PIXEL = 0.005f;
const float Orbit::PITCH_MIN = 0.1f;
const float Orbit::PITCH_MAX = atan(1) * 2 - Orbit::PITCH_MIN;

Orbit::Orbit(const float angle, const float pitch, const float zoom) :
	dragging(false),
	angle(angle),
	pitch(pitch),
	zoom(zoom) {
	updateMatrix();
}

void Orbit::mouseGrab() {
	dragging = true;
}

void Orbit::mouseMove(const int x, const int y) {
	if(dragging) {
		const int dx = x - this->x;
		const int dy = y - this->y;

		angle += dx * RADIANS_PER_PIXEL;
		pitch += dy * RADIANS_PER_PIXEL;

		if(pitch < PITCH_MIN)
			pitch = PITCH_MIN;
		else if(pitch > PITCH_MAX)
			pitch = PITCH_MAX;

		updateMatrix();
	}

	this->x = x;
	this->y = y;
}

void Orbit::mouseRelease() {
	dragging = false;
}

const Matrix &Orbit::getMatrix() const {
	return view;
}

void Orbit::updateMatrix() {
	view = Matrix::makeLookAt(
		Vector(
			cos(angle) * cos(pitch),
			sin(pitch),
			sin(angle) * cos(pitch)) * zoom,
		Vector(),
		UP);
}