#include "path.h"

#include <array>

using namespace LRender;

const float Path::CONNECT_THRESHOLD_DOT = 0.55f;

Path::Path(const Node &node) :
	nodes({ node }) {

}

const std::vector<Node> &Path::getNodes() const {
	return nodes;
}

const std::vector<Node> &Path::getRoot() const {
	return root;
}

const void Path::transform(
	std::vector<Vector> &vectors,
	const std::vector<Node>::const_iterator &node) const {
	if(root.size() > 0 && node == nodes.begin()) {
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

void Path::add(const Node &node) {
	nodes.push_back(node);
}

void Path::calculateTopDist(const size_t offset) {
	for(size_t i = 0; i < nodes.size(); ++i) {
		const size_t dist = nodes.size() - i - 1 + offset;

		if(dist > nodes[i].topDist)
			nodes[i].topDist = dist;
	}
}

void Path::setRoot(const std::vector<Node> &root) {
	this->root = root;
}

size_t Path::size() const {
	return nodes.size();
}

void Path::transform(
	std::vector<Vector> &vectors,
	const Quaternion q) const {
	for(auto &vector : vectors)
		vector = q * vector;
}
void Path::transform(
	std::vector<Vector> &vectors,
	const Quaternion qa, const Quaternion qb) const {
	for(auto &vector : vectors) {
		auto length = vector.length();

		vector = qa * vector + qb * vector;
		vector = (length * vector) / vector.length();
	}
}