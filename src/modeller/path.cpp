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

void Path::setRadius(const float radius) {
	nodes[0].radius = radius;
}

void Path::attach(int index) {
	if(index == -1)
		return;

	attachments.push_back(Attachment(nodes.size() - 1, index));
}

void Path::taper(std::vector<Path> &paths) {
	const size_t size = nodes.size();

	for(size_t i = 1; i < size; ++i)
		nodes[i].radius = nodes[0].radius * (1 - (float(i) / (size - 1)));
	
	for(auto attachment : attachments) {
		paths[attachment.path].setRadius(nodes[attachment.node].radius);
	}
}

size_t Path::size() const {
	return nodes.size();
}

Path::Attachment::Attachment(
	size_t node,
	size_t path) :
	node(node),
	path(path) {

}