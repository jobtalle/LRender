#include "standardLeaf.h"

using namespace LRender;

StandardLeaf::StandardLeaf(
	const Type type,
	const Vector &position,
	const Quaternion &orientation) :
	type(type),
	position(position),
	orientation(orientation) {
	
}

StandardLeaf::Type StandardLeaf::getType() const {
	return type;
}

const Vector &StandardLeaf::getPosition() const {
	return position;
}

const Quaternion &StandardLeaf::getOrientation() const {
	return orientation;
}
