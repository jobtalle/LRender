#pragma once

#include "math/matrix.h"
#include "math/vector.h"

#include <math.h>

namespace LRender {
	class Orbit final {
	public:
		Orbit(
			const float angle = atan(1),
			const float pitch = atan(1),
			const float zoom = 1.5f);
		void setFocus(const Vector &focus);
		void mouseGrabDrag();
		void mouseGrabPan();
		void mouseMove(const int x, const int y);
		void mouseReleaseDrag();
		void mouseReleasePan();
		void zoomIn();
		void zoomOut();
		const Matrix &getMatrix() const;
		const Vector &getFocus() const;

	private:
		static const Vector UP;
		static const float RADIANS_PER_PIXEL;
		static const float PITCH_MIN;
		static const float PITCH_MAX;
		static const float ZOOM_MIN;
		static const float ZOOM_MAX;
		static const float ZOOM_FACTOR;

		Vector eye;
		Vector focus;
		Matrix view;
		int x, y;
		bool dragging;
		bool panning;
		float angle;
		float pitch;
		float zoom;

		void updateEye();
		void updateMatrix();
	};
}