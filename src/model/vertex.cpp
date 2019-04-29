#include "vertex.h"

using namespace LRender;

Vertex::Vertex(const Vector &position, const Vector &normal, const float cu, const float cv) :
	position(position),
	normal(normal),
	cu(cu),
	cv(cv) {

}