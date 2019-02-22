#include "leaf.h"

using namespace LRender;

Leaf::Leaf() {

}

const std::list<Branch> &Leaf::getBranches() const {
	return branches;
}