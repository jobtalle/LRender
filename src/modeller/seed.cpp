#include "seed.h"

using namespace LRender;

Seed::Seed(const Vector &position) :
	position(position),
	topDist(0) {

}

void Seed::setTopDist(const size_t topDist) {
	this->topDist = topDist;
}

size_t Seed::getTopDist() const {
	return topDist;
}

const Vector &Seed::getPosition() const {
	return position;
}