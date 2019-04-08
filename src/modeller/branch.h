#pragma once

#include "modeller/node.h"
#include "modeller/seed.h"
#include "math/vector.h"

#include <vector>

namespace LRender {
	class Branch final {
	public:
		template <class ChildType>
		class Child {
		public:
			Child(size_t index, ChildType *child);

			const size_t index;
			ChildType *const child;
		};

		Branch(const Node &node);
		const std::vector<Node> &getNodes() const;
		void transform(
			std::vector<Vector> &vectors,
			const std::vector<Node>::const_iterator &node) const;
		void add(const Node &node);
		void add(Branch *branch);
		void add(Seed *seed);
		void calculateTopDist(size_t offset = 0);
		void setRoot(const std::vector<Node> &root);
		size_t size() const;
		const std::vector<Child<Branch>> &getBranches() const;

	private:
		static const float CONNECT_THRESHOLD_DOT;

		std::vector<Node> root;
		std::vector<Node> nodes;
		std::vector<Child<Branch>> branches;
		std::vector<Child<Seed>> seeds;

		static void transform(
			std::vector<Vector> &vectors,
			const Quaternion &q);
		static void transform(
			std::vector<Vector> &vectors,
			const Quaternion &qa, const Quaternion &qb);
	};
}