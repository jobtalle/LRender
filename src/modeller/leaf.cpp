#include "leaf.h"

using namespace LRender;

Leaf::Leaf() :
	area(0) {

}

void Leaf::addArea(const float area) {
	this->area += area;
}

const std::list<Branch> &Leaf::getBranches() const {
	return branches;
}

float Leaf::getArea() const {
	return area;
}