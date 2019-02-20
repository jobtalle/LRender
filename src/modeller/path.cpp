#include "path.h"

using namespace LRender;

Path::Path(const Node &root) :
	nodes({ root }) {

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

size_t Path::size() const {
	return nodes.size();
}