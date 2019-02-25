#pragma once

#include "modeller/node.h"
#include "modeller/seed.h"
#include "math/vector.h"

#include <vector>

namespace LRender {
	class Branch final {
	public:
		struct ChildBranch {
			ChildBranch(const size_t index, Branch *child);

			const size_t index;
			Branch *child;
		};

		struct ChildSeed {
			ChildSeed(const size_t index, Seed *child);

			const size_t index;
			Seed *child;
		};

		Branch(const Node &node);
		const std::vector<Node> &getNodes() const;
		const std::vector<Node> &getRoot() const;
		const void transform(
			std::vector<Vector> &vectors,
			const std::vector<Node>::const_iterator &node) const;
		void add(const Node &node);
		void add(Branch *branch);
		void add(Seed *seed);
		void calculateTopDist(const size_t offset = 0);
		void setRoot(const std::vector<Node> &root);
		size_t size() const;
		const std::vector<ChildBranch> &getChildren() const;

	private:
		static const float CONNECT_THRESHOLD_DOT;

		std::vector<Node> root;
		std::vector<Node> nodes;
		std::vector<ChildBranch> branches;
		std::vector<ChildSeed> seeds;

		void transform(
			std::vector<Vector> &vectors,
			const Quaternion q) const;
		void transform(
			std::vector<Vector> &vectors,
			const Quaternion qa, const Quaternion qb) const;
	};
}