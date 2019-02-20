#pragma once

#include "node.h"

#include <vector>

namespace LRender {
	class Path final {
	public:
		Path(const Node &root);
		const std::vector<Node> &getNodes() const;
		void add(const Node &node);
		void calculateTopDist(const size_t offset = 0);
		size_t size() const;

	private:
		std::vector<Node> nodes;
	};
}