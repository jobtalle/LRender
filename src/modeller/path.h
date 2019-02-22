#pragma once

#include "node.h"
#include "../math/vector.h"

#include <vector>

namespace LRender {
	class Path final {
	public:
		Path(const Node &node);
		const std::vector<Node> &getNodes() const;
		const std::vector<Node> &getRoot() const;
		const void transform(
			std::vector<Vector> &vectors,
			const std::vector<Node>::const_iterator &node) const;
		void add(const Node &node);
		void calculateTopDist(const size_t offset = 0);
		void setRoot(const std::vector<Node> &root);
		size_t size() const;

	private:
		static const float CONNECT_THRESHOLD_DOT;

		std::vector<Node> root;
		std::vector<Node> nodes;

		void transform(
			std::vector<Vector> &vectors,
			const Quaternion q) const;
		void transform(
			std::vector<Vector> &vectors,
			const Quaternion qa, const Quaternion qb) const;
	};
}