#pragma once

#include "math/vector.h"
#include "math/quaternion.h"

namespace LRender {
	class StandardLeaf final {
	public:
		enum Type {
			A,
			COUNT
		};

		StandardLeaf(
			Type type,
			const Vector &position,
			const Quaternion &orientation);
		Type getType() const;
		const Vector &getPosition() const;
		const Quaternion &getOrientation() const;

	private:
		const Type type;
		const Vector position;
		const Quaternion orientation;
	};
}