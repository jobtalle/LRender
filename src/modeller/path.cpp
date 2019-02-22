#include "path.h"

#include <array>

using namespace LRender;

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
	const size_t nodeIndex) const {
	if(root.size() > 0 && nodeIndex == 0) {
		if(root.size() == 1)
			transform(vectors, root[0].getHeading());
		else
			transform(vectors, root[0].getHeading(), root[1].getHeading());
	}
	else if(nodeIndex == nodes.size() - 1)
		transform(vectors, nodes[nodeIndex].getHeading());
	else
		transform(vectors, nodes[nodeIndex].getHeading(), nodes[nodeIndex + 1].getHeading());
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
	nodes.erase(nodes.begin());
	nodes.insert(nodes.begin(), *root.begin());

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
	for(auto &vector : vectors)
		vector = ((qa * vector + qb * vector) * 0.5f).normalize();
}