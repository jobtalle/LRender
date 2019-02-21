#pragma once

#include "node.h"

#include <vector>

namespace LRender {
	class Path final {
	public:
		Path(const Node &node);
		const std::vector<Node> &getNodes() const;
		void add(const Node &node);
		void calculateTopDist(const size_t offset = 0);
		void setRoot(const std::vector<Node> &root);
		void setAnchor(const Node &node);
		size_t size() const;
		bool isChild() const;
		bool isAnchor() const;

	private:
		bool child = false;
		bool anchor = false;
		std::vector<Node> nodes;
	};
}