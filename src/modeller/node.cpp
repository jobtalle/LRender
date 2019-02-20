#include "node.h"
#include "modeller.h"

using namespace LRender;

Node::Node(const Vector &position, const Quaternion &heading) :
	position(position),
	heading(heading) {

}

Node &Node::extrude(const float distance) {
	position += heading * Modeller::UP * distance;

	return *this;
}