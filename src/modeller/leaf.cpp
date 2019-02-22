#include "leaf.h"

using namespace LRender;

Leaf::Leaf(const std::vector<Branch> &branches) :
	branches(branches) {

}

const std::vector<Branch> &Leaf::getBranches() const {
	return branches;
}