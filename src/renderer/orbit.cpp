#include "orbit.h"

using namespace LRender;

const Vector Orbit::UP = Vector(0, 1, 0);
const float Orbit::RADIANS_PER_PIXEL = 0.005f;
const float Orbit::PITCH_MIN = 0;
const float Orbit::PITCH_MAX = atan(1) * 2 - 0.0001f;
const float Orbit::ZOOM_MIN = 0.1f;
const float Orbit::ZOOM_MAX = 1000;
const float Orbit::ZOOM_FACTOR = 0.15f;

Orbit::Orbit(const float angle, const float pitch, const float zoom) :
	dragging(false),
	panning(false),
	angle(angle),
	pitch(pitch),
	zoom(zoom) {
	updateEye();
	updateMatrix();
}

void Orbit::setFocus(const Vector &focus) {
	this->focus = focus;

	updateMatrix();
}

void Orbit::mouseGrabDrag() {
	dragging = true;
}

void Orbit::mouseGrabPan() {
	panning = true;
}

void Orbit::mouseMove(const int x, const int y) {
	const int dx = x - this->x;
	const int dy = y - this->y;

	if(dragging) {
		angle += dx * RADIANS_PER_PIXEL;
		pitch += dy * RADIANS_PER_PIXEL;

		if(pitch < PITCH_MIN)
			pitch = PITCH_MIN;
		else if(pitch > PITCH_MAX)
			pitch = PITCH_MAX;

		updateEye();
		updateMatrix();
	}
	else if(panning) {
		Vector right = UP.cross(-eye).normalize();
		Vector up = right.cross(-eye).normalize();

		focus += right * dx * zoom * 0.002f - up * dy * zoom * 0.002f;

		updateMatrix();
	}

	this->x = x;
	this->y = y;
}

void Orbit::mouseReleaseDrag() {
	dragging = false;
}

void Orbit::mouseReleasePan() {
	panning = false;
}

void Orbit::zoomIn() {
	zoom *= 1 - ZOOM_FACTOR;

	if(zoom < ZOOM_MIN)
		zoom = ZOOM_MIN;

	updateEye();
	updateMatrix();
}

void Orbit::zoomOut() {
	zoom *= 1 + ZOOM_FACTOR;

	if(zoom > ZOOM_MAX)
		zoom = ZOOM_MAX;

	updateEye();
	updateMatrix();
}

const Matrix &Orbit::getMatrix() const {
	return view;
}

const Vector& Orbit::getFocus() const {
	return focus;
}

void Orbit::updateEye() {
	eye = Vector(
		cos(angle) * cos(pitch),
		sin(pitch),
		sin(angle) * cos(pitch)) * zoom;
}

void Orbit::updateMatrix() {
	view = Matrix::makeLookAt(
		focus + eye,
		focus,
		UP);
}