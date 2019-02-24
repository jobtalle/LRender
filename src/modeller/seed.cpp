#include "seed.h"

using namespace LRender;

Seed::Seed(const Vector &position) :
	position(position) {

}

const Vector &Seed::getPosition() const {
	return position;
}