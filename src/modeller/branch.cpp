#include "branch.h"

using namespace LRender;

const float Branch::CONNECT_THRESHOLD_DOT = 0.55f;

Branch::Branch(const Node &node) :
	nodes({ node }) {

}

const std::vector<Node> &Branch::getNodes() const {
	return nodes;
}

void Branch::transform(
	std::vector<Vector> &vectors,
	const std::vector<Node>::const_iterator &node) const {
	if(node == nodes.begin() && !root.empty()) {
		if(root.size() == 1)
			transform(vectors, root[0].getHeading());
		else {
			if(node != nodes.end() - 1) {
				auto dRoot = (root[1].position - root[0].position).normalize();
				const auto dPath = ((node + 1)->position - node->position).normalize();
				
				if(dRoot.dot(dPath) > CONNECT_THRESHOLD_DOT)
					transform(vectors, root[0].getHeading(), root[1].getHeading());
				else
					transform(vectors, node->getHeading(), (node + 1)->getHeading());
			}
		}
	}
	else if(node == nodes.end() - 1)
		transform(vectors, node->getHeading());
	else
		transform(vectors, node->getHeading(), (node + 1)->getHeading());
}

void Branch::add(const Node &node) {
	nodes.push_back(node);
}

void Branch::add(Branch *branch) {
	branches.emplace_back(nodes.size() - 1, branch);
}

void Branch::add(Seed *seed) {
	seeds.emplace_back(nodes.size() - 1, seed);
}

void Branch::calculateTopDist(const size_t offset) {
	for(size_t i = 0; i < nodes.size(); ++i) {
		const auto dist = nodes.size() - i - 1 + offset;

		if(dist > nodes[i].topDist)
			nodes[i].topDist = dist;
	}
	
	for(Child<Seed> &seed : seeds)
		seed.child->setTopDist(nodes[seed.index].topDist);
}

void Branch::setRoot(const std::vector<Node> &root) {
	this->root = root;
}

size_t Branch::size() const {
	return nodes.size();
}

const std::vector<Branch::Child<Branch>> &Branch::getBranches() const {
	return branches;
}

void Branch::transform(
	std::vector<Vector> &vectors,
	const Quaternion &q) {
	for(auto &vector : vectors)
		vector = q * vector;
}
void Branch::transform(
	std::vector<Vector> &vectors,
	const Quaternion &qa, const Quaternion &qb) {
	for(auto &vector : vectors) {
		const auto length = vector.length();

		vector = qa * vector + qb * vector;
		vector = (length * vector) / vector.length();
	}
}

template <class ChildType>
Branch::Child<ChildType>::Child(const size_t index, ChildType *const child) :
	index(index),
	child(child) {

}