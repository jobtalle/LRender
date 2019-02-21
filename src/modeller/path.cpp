#include "path.h"

#include <array>

using namespace LRender;

Path::Path(const Node &node) :
	nodes({ node }) {

}

const std::vector<Node> &Path::getNodes() const {
	return nodes;
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
	nodes.insert(nodes.begin(), root.begin(), root.end());

	child = true;
}

void Path::setAnchor(const Node &node) {
	nodes.insert(nodes.begin(), node);

	anchor = true;
}

size_t Path::size() const {
	return nodes.size();
}

bool Path::isChild() const {
	return child;
}

bool Path::isAnchor() const {
	return anchor;
}