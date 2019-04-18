#include "node.h"

using namespace LRender;

const Vector Node::UP(0, 1, 0);
const Vector Node::AXIS_PITCH(0, 0, 1);
const Vector Node::AXIS_ROLL(0, 1, 0);
const Vector Node::AXIS_YAW(1, 0, 0);

Node::Node(const Vector &position, const float angle) :
	position(position),
	heading(Quaternion::makeRotation(UP, angle)),
	topDist(0) {

}

Node &Node::extrude(const float distance) {
	position += heading * UP * distance;

	return *this;
}

Node &Node::roll(const float radians) {
	heading.rotate(AXIS_ROLL, radians);
	rollCompensation.rotate(AXIS_ROLL, -radians);

	return *this;
}

Node &Node::pitch(const float radians) {
	heading.rotate(AXIS_PITCH, radians);

	return *this;
}

Node &Node::yaw(const float radians) {
	heading.rotate(AXIS_YAW, radians);

	return *this;
}

Quaternion Node::getHeading() const {
	return heading * rollCompensation;
}

bool Node::operator==(const Node &other) const {
	return position == other.position && heading == other.heading;
}