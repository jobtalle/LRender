#include "branch.h"

#include <array>

using namespace LRender;

const float Branch::CONNECT_THRESHOLD_DOT = 0.55f;

Branch::Branch(const Node &node) :
	nodes({ node }) {

}

const std::vector<Node> &Branch::getNodes() const {
	return nodes;
}

const std::vector<Node> &Branch::getRoot() const {
	return root;
}

const void Branch::transform(
	std::vector<Vector> &vectors,
	const std::vector<Node>::const_iterator &node) const {
	if(node == nodes.begin() && root.size() > 0) {
		if(root.size() == 1)
			transform(vectors, root[0].getHeading());
		else {
			if(node != nodes.end() - 1) {
				Vector dRoot = (root[1].position - root[0].position).normalize();
				Vector dPath = ((node + 1)->position - node->position).normalize();
				
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
	children.push_back(Child(nodes.size() - 1, branch));
}

void Branch::calculateTopDist(const size_t offset) {
	for(size_t i = 0; i < nodes.size(); ++i) {
		const size_t dist = nodes.size() - i - 1 + offset;

		if(dist > nodes[i].topDist)
			nodes[i].topDist = dist;
	}
}

void Branch::setRoot(const std::vector<Node> &root) {
	this->root = root;
}

size_t Branch::size() const {
	return nodes.size();
}

const std::vector<Branch::Child> &Branch::getChildren() const {
	return children;
}

void Branch::transform(
	std::vector<Vector> &vectors,
	const Quaternion q) const {
	for(auto &vector : vectors)
		vector = q * vector;
}
void Branch::transform(
	std::vector<Vector> &vectors,
	const Quaternion qa, const Quaternion qb) const {
	for(auto &vector : vectors) {
		auto length = vector.length();

		vector = qa * vector + qb * vector;
		vector = (length * vector) / vector.length();
	}
}

Branch::Child::Child(const size_t index, const Branch *child) :
	index(index),
	child(child) {

}