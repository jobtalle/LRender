#include "node.h"
#include "modeller.h"

using namespace LRender;

Node::Node(const Vector &position, const Quaternion &heading) :
	position(position),
	heading(heading),
	radius(0) {

}

Node &Node::extrude(const float distance) {
	position += heading * Modeller::UP * distance;

	return *this;
}

bool Node::operator==(const Node &other) const {
	return position == other.position && heading == other.heading && radius == other.radius;
}